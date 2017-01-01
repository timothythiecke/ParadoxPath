#include <iostream>
#include <set>
#include <vector>

struct Node
{
	Node() :
		left(nullptr),
		right(nullptr),
		up(nullptr),
		down(nullptr),
		previous(nullptr),
		index(0),
		traversable(false),
		visited(false),
		distance(UINT32_MAX)
	{
		
	}

	Node* left;
	Node* right;
	Node* up;
	Node* down;
	Node* previous;

	unsigned int index;
	unsigned int distance;
	bool traversable;
	bool visited;
};



/*
Visualizes the nodes in the console window, both the nodes where the path can continue
and the indices to help with debugging
*/
void PrintInfo(const Node* nNodes, const int nMapWidth, const int nMapHeight)
{
	// Map / traversable
	for (int j = 0; j < nMapHeight; ++j)
	{
		for (int i = 0; i < nMapWidth; ++i)
		{
			std::cout << nNodes[nMapWidth * j + i].traversable << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;

	// 1D indices
	for (int j = 0; j < nMapHeight; ++j)
	{
		for (int i = 0; i < nMapWidth; ++i)
		{
			std::cout << nNodes[nMapWidth * j + i].index << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;

	// 2D indices
	for (int j = 0; j < nMapHeight; ++j)
	{
		for (int i = 0; i < nMapWidth; ++i)
		{
			std::cout << "[" << i << ", " << j << "] ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}



void LogResult(const int inStartIndex, const int inStepAmount, const int* inPathBuffer)
{
	if (inStepAmount == -1)
		std::cout << "Unreachable solution!" << std::endl;
	else
	{
		std::cout << "Found solution with " << inStepAmount << " elements" << std::endl;

		std::cout << inStartIndex << " -> ";

		for (int i = 0; i < inStepAmount; ++i)
		{
			std::cout << inPathBuffer[i];

			if (i != inStepAmount - 1)
				std::cout << " -> ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}



int FindPath(const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize)
{
	// Populate node array
	const int node_amount = nMapWidth * nMapHeight;
	Node* nodes = new Node[node_amount];

	for (int j = 0; j < nMapHeight; ++j)
	{
		for (int i = 0; i < nMapWidth; ++i)
		{
			const unsigned int index = nMapWidth * j + i; // 2D -> 1D

			// Fill the nodes with the information contained in the map
			nodes[index].traversable = pMap[index] != 0; // Takes care of the force bool true/false warning (C4800)
			nodes[index].index = index;

			// Fix pointers in nodes so there are neighbours to consider
			if (i != 0)
				nodes[index].left = &nodes[index - 1];

			if (i != nMapWidth - 1)
				nodes[index].right = &nodes[index + 1];

			if (j != 0)
				nodes[index].up = &nodes[index - nMapWidth];

			if (j != nMapHeight - 1)
				nodes[index].down = &nodes[index + nMapWidth];
		}
	}

	// Print to help debugging
	PrintInfo(nodes, nMapWidth, nMapHeight);

	//---------------------------
	// Apply Dijkstra's algorithm
	//---------------------------
	// Assign a tentative distance value of zero to the initial node (current)
	const int initial_index = nMapWidth * nStartY + nStartX;
	const int target_index = nMapWidth * nTargetY + nTargetX;
	
	if (initial_index < 0 || initial_index >= node_amount)
	{
		delete[] nodes;
		return -1; // Invalid initial index!
	}
		
	if (target_index < 0 || target_index >= node_amount)
	{
		delete[] nodes;
		return -1; // Invalid target index!
	}
		
	// Set initial node as current, mark all other nodes unvisited
	Node* initial_node = nodes + initial_index;
	Node* current_node = initial_node;
	Node* target_node = nodes + target_index;

	if (initial_node != nullptr)
	{
		initial_node->visited = true;
		initial_node->distance = 0;
	}
	
	// Create a set of all unvisited nodes called the unvisited set
	std::set<Node*> unvisited_nodes;
	for (int i = 0; i < node_amount; ++i)
	{
		if (!nodes[i].visited)
			unvisited_nodes.insert(&nodes[i]);
	}
	
	// Loop
	bool terminate_algorithm_unreachable = false;
	while (target_node != nullptr && !target_node->visited && !terminate_algorithm_unreachable && current_node != nullptr)
	{
		// For all neighbours, that are unvisited, and are traversable
		// Calculate tentative distance
		// Compare this distance to current distance value
		// If smaller, assign new distance value
		// Tentative distance is calculated by distance of node + distance between next node and current node
		std::vector<Node*> neighbours;
		neighbours.reserve(4);

		neighbours.push_back(current_node->left);
		neighbours.push_back(current_node->right);
		neighbours.push_back(current_node->up);
		neighbours.push_back(current_node->down);

		for (Node* node : neighbours)
		{
			if (node != nullptr && node->traversable)
			{
				const unsigned int tentative_distance = current_node->distance + 1;

				if (tentative_distance < node->distance)
				{
					node->distance = tentative_distance;
					node->previous = current_node;
				}
			}
		}

		// Select the node with the smallest tentative distance to be marked as the next current node
		unsigned int max = INT32_MAX;
		for (Node* node : unvisited_nodes)
		{
			if (node->distance < max)
			{
				max = node->distance;
				current_node = node;
			}
		}

		// Smallest tentative distance unchanged? unreachable path detected
		if (max == INT32_MAX)
			terminate_algorithm_unreachable = true;

		// Erase from the set and mark visited
		current_node->visited = true;
		unvisited_nodes.erase(current_node);
	}
	
	// No suitable path could be found
	if (terminate_algorithm_unreachable)
	{
		delete[] nodes;
		return -1;
	}

	// A suitable path has been found!
	// Create a sequence of indices (excluding the initial node index)
	std::vector<unsigned int> path;
	path.reserve(nOutBufferSize);

	Node* pathing_node = target_node;
	while (pathing_node->previous != nullptr)
	{
		path.insert(path.begin(), pathing_node->index);
		pathing_node = pathing_node->previous;
	}

	// If the path is larger than the amount of elements the output buffer may hold, we can not reach the target
	// Terminate
	if (path.size() > nOutBufferSize)
	{
		delete[] nodes;
		return -1;
	}

	// Then copy the sequence into the output buffer, and keep track of how many elements there are in the sequence
	unsigned int push_index = 0;
	for (const unsigned int i : path)
	{
		pOutBuffer[push_index++] = i;
	}
	
	delete[] nodes;
	return push_index;
}



int main()
{
	// Case #1
	unsigned char pMap[] = { 1,1,1,1,0,1,0,1,0,1,1,1 };
	int pOutBuffer[12];
	int ret = FindPath(0, 0, 3, 2, pMap, 4, 3, pOutBuffer, 12);

	LogResult(4 * 0 + 0, ret, pOutBuffer);

	// Case #2
	unsigned char pMap2[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
	int pOutBuffer2[7];
	int ret2 = FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, 7);

	LogResult(3 * 0 + 2, ret2, pOutBuffer2);
	
	// Case #3
	unsigned char larger_test[] =
	{
		1,1,1,1,0,
		0,0,0,1,0,
		0,0,0,1,0,
		1,1,1,1,0,
		1,0,0,0,0,
		1,1,1,1,1
	};
	int larger_buffer[20];
	int result = FindPath(0, 0, 4, 5, larger_test, 5, 6, larger_buffer, 20);
	LogResult(0, result, larger_buffer);

	// Case #4 - only one available node
	unsigned char one_available[] = { 1, 0, 0, 0 };
	int one_available_buffer[4];
	int one_available_result = FindPath(0, 0, 1, 1, one_available, 2, 2, one_available_buffer, 4);
	LogResult(0, one_available_result, one_available_buffer);

	// Case #5 - output buffer is too small to hold the output buffer


	return 0;
}