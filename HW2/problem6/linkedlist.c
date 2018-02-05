#include "linkedlist.h"

// Destroy all nodes in the linked list by freeing the memory
void destroy(struct info* head)
{
	struct info* current_node = head;
	struct info* next_node;
	while(current_node->obj.next != NULL)
	{
		current_node = current_node->obj.next;
		next_node = current_node->obj.prev;
		next_node->obj.next = NULL;
		free(current_node);
		current_node = next_node;
	}
	head = NULL;
}

// Add a node to the beginning of the linked list. Should add head node if it does not exist.
struct info* insert_at_beginning(struct info* head, uint32_t userdata)
{
	struct info* newNode;
	newNode = (struct info*)malloc(sizeof(struct info));
	newNode->data = userdata; 
	if (head == NULL)
	{
		head = newNode;
	}
	else 
	{
		head->obj.prev = newNode;
		newNode->obj.next = head;
		head = newNode;
	}
	return head;
}


// Add a node to the end of the linked list. Should add head node if it does not exist.
struct info* insert_at_end(struct info *head, uint32_t userdata)
{
	struct info* newNode;
	newNode = (struct info*)malloc(sizeof(struct info));
	newNode->data = userdata; 
	if (head == NULL)
	{
		newNode->obj.prev = NULL;
		newNode = head;
	}
	else 
	{
		struct info* temp = head;
		while (temp->obj.next != NULL)
		{
			temp = temp->obj.next;                 //reach the end of the list
		}
		temp->obj.next = newNode;
        newNode->obj.prev = temp;
	}
	return head;
}

// Add a node to a given position of the linked list.
struct info* insert_at_position(struct info *head, uint32_t userdata, int index)
{
	int i = 0;
	struct info* newNode;
	newNode = (struct info*)malloc(sizeof(struct info));
	newNode->data = userdata;
	if (head == NULL)
	{
		newNode = head;
	}
	else
	{
		struct info* temp = head;
		while (i < index)
		{
			temp = temp->obj.next;
			i++;
		}
		newNode = temp->obj.next;
		newNode->obj.prev = temp;	
	}
return head;	
}

/*

*/
// Delete a node to the beginning of the linked list
struct info* delete_from_beginning(struct info *head)
{
	if (head == NULL)
	{
		printf("List is empty");
	}
	else 
	{
		struct info* temp = head;
		if (temp->obj.prev == temp->obj.next)
		{
			head == NULL;
			free(temp);
		}
		else
		{
			head = temp->obj.next;
			head->obj.prev = NULL;
			free(temp);
		}
		
	}
	return head;
}

// Delete a node to the end of the linked list
struct info* delete_from_end(struct info *head)
{
	if (head == NULL)
	{
		printf("List is empty");
	}
	else 
	{
		struct info* temp = head;
		if (temp->obj.prev == temp->obj.next)
		{
			head == NULL;
			free(temp);
		}
		else
		{
			while (temp->obj.next != NULL)
			{
			temp = temp->obj.next;                 //reach the end of the list
			}
			struct info* temp1 = temp;
			temp1 = temp->obj.prev;
			temp1->obj.next = NULL;
			free(temp);
		}	
	}
	return head;
}

// Delete a node to a given position of the linked list
struct info* delete_from_position(struct info *head, int index)
{
	int i = 0;

	if (head == NULL)
	{
		printf("List is empty");
	}
	else
	{
		struct info* temp = head;
		if (temp->obj.prev == temp->obj.next)
		{
			head == NULL;
			free(temp);
		}
		else
		{
			while (i < index)
		{
			temp = temp->obj.next;
			i++;
		}
		struct info* temp1 = temp;
		temp1 = temp->obj.prev;
		temp1->obj.next = temp->obj.next;
		free(temp);
		}	
	}
return head;	
}


// Determine the number of links in your linked list
int size(struct info* head)
{
	int s = 1, link_size;
	if (head == NULL)
	{
		printf("Head pointer is null, size is zero");
	}
	else
	{
		while(head->obj.next != NULL)
		{
			head =  head->obj.next;
			s++;
		}
		link_size = s;
	}
	return link_size;
}

uint32_t peak(struct info* head, int index)
{
    int i = 1;
	while (i < index)
		{
			head = head->obj.next;
			i++;
		}
	return head->data;
}

void display(struct info* head)
{
	
	while(head != NULL)
	{
		printf("%i \t", head->data);
		head = head->obj.next;
	}
	printf("\n");
}

