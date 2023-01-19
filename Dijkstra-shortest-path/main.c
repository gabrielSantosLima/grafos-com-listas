
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define DEBUG 0

//Structure to represent edge
typedef struct edge{
	int dest;            // for destination vertex
	int lngth;           // length of edge
	struct edge *next;     
	struct edge *src;    // for head of the list
}edge;

//Structure to represent vertex
typedef struct vertex
{
    	int vertices;
    	struct edge* listArr;  // for adjacency list 
}vertex;


// Structure to represent heap element
typedef struct heap_element{
	int v,d;
}heap_element;

 
// Structure to represent a min heap
typedef struct MinHeap
{
    	int *positionInheap;     	// for index in heap 
	int heap_size;  		// for size of heap    	
   	int number_of_nodes;      	// for number of heap nodes
	heap_element **arr;          
}MinHeap;

void minHeapify(int index,MinHeap* mh);

//create graph consisting of total vertices
vertex* graph_create(int total_vertices)
{
	int i=0;
    	vertex* vertex = (struct vertex*) malloc(sizeof(vertex));
    	vertex->vertices = total_vertices;
 
    	// Adjacency list arr 
    	vertex->listArr=(edge*) malloc(total_vertices * sizeof(edge));
   
     	// Initialize source of adjacency lists with NULL
     	while (i!=total_vertices)
		{
        		vertex->listArr[i].src = NULL;
			i++; 
		}
        if(DEBUG) printf("Graph is created\n"); 
    	return vertex;
}

//Add edges from source to destination and vice versa
void edge_add(vertex* vertex, int v1, int v2, int leng)
{
    	// Add an edge from source v1 to destination v2  
    	edge* srcNode =(edge*) malloc(sizeof(edge));
    	srcNode->dest = v2;
    	srcNode->lngth = leng;
    
	//A new node is added to the adjacency list of v1
    	srcNode->next=vertex->listArr[v1].src;
	
	// Add node to the beginning    
	vertex->listArr[v1].src=srcNode;   
    
    	// Add edge from v2 to v1 
    	edge* destNode =(edge*) malloc(sizeof(edge));
    	destNode->dest = v1;
    	destNode->lngth = leng;
	
	//A new node is added to the adjacency list of v2
    	destNode->next=vertex->listArr[v2].src;
	
	// Add node to the beginning of adjacency list of v2    
    	vertex->listArr[v2].src=destNode;   
    
}
 
//create a minheap with the total number of vertices provided
MinHeap* createMinHeap(int total_vertices)
{
	// Allocate memory for Heap    	
	MinHeap* mh = (MinHeap*) malloc(sizeof(MinHeap));

	// Memory for nodes in heap
    	mh->positionInheap = (int *)malloc(total_vertices * sizeof(int));

	// Assign total number of vertices as the size of heap     	
	mh->heap_size = total_vertices;

	// Initialize number of nodes to 0
    	mh->number_of_nodes = 0;

    	mh->arr =(heap_element**) malloc(total_vertices * sizeof(heap_element*));
	return mh;
}

// create a min heap node with given vertex and dist
heap_element* newheap_element(int ver, int dist)
{
    	heap_element* heap_element =(struct heap_element*) malloc(sizeof(heap_element));
    	heap_element->v = ver;
    	heap_element->d = dist;
    	return heap_element;
}

// decrease value of d for a given vertex v  
void decreaseKey(MinHeap* mh, int v, int dist)
{
    	// Retrieve current index of node
    	int id = mh->positionInheap[v];
        if(DEBUG) printf("initial id:%d\n",id);  
    	// update value of d of the node
    	mh->arr[id]->d = dist;
 
    	while (mh->arr[id]->d < mh->arr[(id - 1) / 2]->d && id)
	{	 
		mh->positionInheap[mh->arr[id]->v] = (id-1)/2;
        	mh->positionInheap[mh->arr[(id-1)/2]->v] = id;

 		//swap
        	heap_element* t = mh->arr[id];
    		mh->arr[id] = mh->arr[(id - 1) / 2];
   		mh->arr[(id - 1) / 2] = t;
                
		// move to parent 
        	id = (id - 1) / 2;
	        if(DEBUG) printf("modified id:%d\n",id); 
    	}
}

//extract minimum distance value node
heap_element* extractMin(MinHeap* mh)
{
	heap_element* min_heap_root;

	// if number of nodes is 0 return null
    	if (mh->number_of_nodes == 0)
        	return NULL;
        else
	{ 
		if(DEBUG) printf("number of nodes:%d\n",mh->number_of_nodes); 
    		// store the value of arr[0] as the root of min heap
    		min_heap_root = mh->arr[0];
 
    		// Replace the root node with last node
    		heap_element* lnode = mh->arr[mh->number_of_nodes - 1];
    		mh->arr[0] = lnode;
 
    		// Update last node's positionIn heap
    		mh->positionInheap[min_heap_root->v] = mh->number_of_nodes-1;
    		mh->positionInheap[lnode->v] = 0;
 
    		// Reduce heap number_of_nodes
   		mh->number_of_nodes= mh->number_of_nodes-1;

		// Heapify
    		minHeapify(0,mh);
 	}
    return min_heap_root;
}

//min heapify
void minHeapify(int index,MinHeap* mh)
{
    	int least;
    	int l, r;
        heap_element *leastNode;
	heap_element *indNode;
    
    
    	least = index;
    	l = (2*(index)) + 1;  // left child 
    	r = (2*(index)) + 2;  // right child
 
    	if (l < mh->number_of_nodes)
    	{  
      		if(mh->arr[l]->d < mh->arr[least]->d )
      		{
			least = l;
		}	
    	}

    	if (r < mh->number_of_nodes)
    	{
       		if(mh->arr[r]->d < mh->arr[least]->d )
       		{
			least = r;
		} 
    	}		 
      
    	if (least != index)
    	{
        	
        	leastNode = mh->arr[least];
        	indNode = mh->arr[index];
 
        	mh->positionInheap[leastNode->v] = index;
        	mh->positionInheap[indNode->v] = least;
 
        	// Swap nodes
                heap_element* t = mh->arr[least];
    	 	mh->arr[least] = mh->arr[index];
   	 	mh->arr[index] = t;  	        

		//minheapify
	 	minHeapify(least,mh);
    }
}

int main(int argc, char* argv[])
{
	int k=0,v,i,src,des,edgeLength,total_vertices,total_edges, maximum,total_cost=0;
	
	// total number of vertices
	scanf("%d %d", &total_vertices,&total_edges);
	
	// if number of vertex=0        
	if(total_vertices==0)
 		exit(0);
	
        
        vertex* vertex = graph_create(total_vertices);
    
	//accept length of edges
 	for(k = 0; k<total_edges;k++)
	{	
		scanf("%d %d %d",&src,&des,&edgeLength);

		//using the given src and destination, add edges
		edge_add(vertex, src,des, edgeLength);
        }

        // Array to maintain distance of vertices from origin 
        int dist[total_vertices];      
 
    	// create a MinHeap with the total_vertices
    	MinHeap* mh = createMinHeap(total_vertices);
 
        // Initially number_of_nodes of min heap is equal to total_vertices
    	mh->number_of_nodes = total_vertices;

    	// Initialize min heap 
    	for (i = 0; i < total_vertices; ++i)
    	{
        	dist[i] = INT_MAX;        // distance of each vertex is set to infinity initially 
        	mh->arr[i] = newheap_element(i, dist[i]);
        	mh->positionInheap[i] = i;
    	}	
 
        // distance of source is 0
    	mh->arr[0] = newheap_element(0, dist[0]);
    	mh->positionInheap[0]   = 0;
    	dist[0] = 0;
    	decreaseKey(mh, 0, dist[0]);
    	
        // while the number of nodes in the min heap is not equal to 0 run the loop
    	while (!(mh->number_of_nodes == 0))
    	{
        	// get the minimum distance value vertex
        	heap_element* heap_element = extractMin(mh);

		// vertex having minimum distance value is vrtex,say        	
		int vrtex = heap_element->v; 
 
        	//visit all adjacent vertices of vrtex and update distance values
        	edge* nodeAl = vertex->listArr[vrtex].src;
        	
		while (nodeAl != NULL)
        	{
            		int v = nodeAl->dest;
			if(DEBUG) printf("destination vertex:%d\n",v);  
            		if(dist[vrtex] != INT_MAX)   // if vertex distance is not infinity
                        {
				if(mh->positionInheap[v] < mh->number_of_nodes) 
				{ 
					//RELAX
                                	if(nodeAl->lngth + dist[vrtex] < dist[v])
					{
						dist[v] = dist[vrtex] + nodeAl->lngth;
						decreaseKey(mh, v, dist[v]);
					}       
				}
			}
            		nodeAl = nodeAl->next;
        	}
    	}
 
    	// print the result
   	for(i=0;i<total_vertices;++i)
      	{
                 if(dist[0]<dist[i])
			{ 
				dist[0]=dist[i];
				maximum=i;
			}

	}
      	printf("%d %d\n",maximum,dist[0]);  
}
