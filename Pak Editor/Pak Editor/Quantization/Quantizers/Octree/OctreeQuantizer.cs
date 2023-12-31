﻿using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using SimplePaletteQuantizer.Helpers;

namespace SimplePaletteQuantizer.Quantizers.Octree
{
    /// <summary>
    /// The idea here is to build a tree structure containing always a maximum of K different 
    /// colors. If a further color is to be added to the tree structure, its color value has 
    /// to be merged with the most likely one that is already in the tree. The both values are 
    /// substituted by their mean. 
    ///
    /// The most important data structure are the nodes of the octree. Each inner node of the 
    /// octree contain a maximum of eight successors, the leave nodes keep information for the 
    /// color value (colorvalue), the color index (colorindex), and a counter (colorcount) for 
    /// the pixel that are already mapped to a particular leave. Because each of the red, green 
    /// and blue value is between 0 and 255 the maximum depth of the tree is eight. In level i 
    /// Bit i of RGB is used as selector for the successors. 
    ///
    /// The octree is constructed during reading the image that is to be quantized. Only that 
    /// parts of the octree are created that are really needed. Initially the first K values 
    /// are represented exactly (in level eight). When the number of leaves nodes (currentK) 
    /// exceeds K, the tree has to reduced. That would mean that leaves at the largest depth 
    /// are substituted by their predecessor.
    /// </summary>
    public class OctreeQuantizer : IColorQuantizer
    {
        private OctreeNode root;
        private readonly List<OctreeNode>[] levels;

        /// <summary>
        /// Initializes a new instance of the <see cref="Octree"/> class.
        /// </summary>
        public OctreeQuantizer()
        {
            // initializes the octree level lists
            levels = new List<OctreeNode>[7];

            // creates the octree level lists
            for (Int32 level = 0; level < 7; level++)
            {
                levels[level] = new List<OctreeNode>();
            }

            // creates a root node
            root = new OctreeNode(0, this);
        }

        #region | Calculated properties |

        /// <summary>
        /// Gets the leaf nodes only (recursively).
        /// </summary>
        /// <value>All the tree leaves.</value>
        internal IEnumerable<OctreeNode> Leaves
        {
            get { return root.ActiveNodes.Where(node => node.IsLeaf); }
        }

        #endregion

        #region | Methods |

        /// <summary>
        /// Adds the node to a level node list.
        /// </summary>
        /// <param name="level">The depth level.</param>
        /// <param name="octreeNode">The octree node to be added.</param>
        internal void AddLevelNode(Int32 level, OctreeNode octreeNode)
        {
            levels[level].Add(octreeNode);
        }

        #endregion

        #region << IColorQuantizer >>

        /// <summary>
        /// Adds the color to quantizer.
        /// </summary>
        /// <param name="color">The color to be added.</param>
        public void AddColor(Color color)
        {
            color = QuantizationHelper.ConvertAlpha(color);
            root.AddColor(color, 0, this);
        }

        /// <summary>
        /// Gets the palette with specified count of the colors.
        /// </summary>
        /// <param name="colorCount">The color count.</param>
        /// <returns></returns>
        public List<Color> GetPalette(Int32 colorCount)
        {
            List<Color> result = new List<Color>();
            Int32 leafCount = Leaves.Count();
            Int32 paletteIndex = 0;

            // goes thru all the levels starting at the deepest, and goes upto a root level
            for (Int32 level = 6; level >= 0; level--)
            {
                // if level contains any node
                if (levels[level].Count > 0)
                {
                    // orders the level node list by pixel presence (those with least pixels are at the top)
                    IEnumerable<OctreeNode> sortedNodeList = levels[level].
                        OrderBy(node => node.ActiveNodesPixelCount);

                    // removes the nodes unless the count of the leaves is lower or equal than our requested color count
                    foreach (OctreeNode node in sortedNodeList)
                    {
                        // removes a node
                        leafCount -= node.RemoveLeaves();
                        
                        // if the count of leaves is lower then our requested count terminate the loop
                        if (leafCount <= colorCount) break;
                    }

                    // if the count of leaves is lower then our requested count terminate the level loop as well
                    if (leafCount <= colorCount) break;
                    
                    // otherwise clear whole level, as it is not needed anymore
                    levels[level].Clear();
                }
            }

            // goes through all the leaves that are left in the tree (there should now be less or equal than requested)
            foreach (OctreeNode node in Leaves)
            {
                // adds then to a palette
                result.Add(node.Color);

                // and marks the node with a palette index
                node.SetPaletteIndex(paletteIndex++);
            }

            // we're unable to reduce the Octree with enough precision, and the leaf count is zero
            if (result.Count == 0)
            {
                throw new NotSupportedException("The Octree contains after the reduction 0 colors, it may happen for 1-16 colors because it reduces by 1-8 nodes at time. Should be used on 8 or above to ensure the correct functioning.");
            }

            // returns the palette
            return result;
        }

        /// <summary>
        /// Gets the index of the palette for specific color.
        /// </summary>
        /// <param name="color">The color.</param>
        /// <returns></returns>
        public Int32 GetPaletteIndex(Color color)
        {
            color = QuantizationHelper.ConvertAlpha(color);

            // retrieves a palette index
            return root.GetPaletteIndex(color, 0);
        }

        /// <summary>
        /// Gets the color count.
        /// </summary>
        /// <returns></returns>
        public Int32 GetColorCount()
        {
            // calculates the number of leaves, by parsing the whole tree
            return Leaves.Count();
        }

        /// <summary>
        /// Clears this instance.
        /// </summary>
        public void Clear()
        {
            // clears all the node list levels
            foreach (List<OctreeNode> level in levels)
            {
                level.Clear();
            }

            // creates a new root node (thus throwing away the old tree)
            root = new OctreeNode(0, this);
        }

        #endregion
    }
}


