/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  School of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{

    printf("[----- [김상수] [2018038078] -----]\n");
    
	QueueType *cQ = createQueue();
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = "); 
		scanf(" %c", &command);

		switch(command) {
		case 'i': 
        case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': 
        case 'D':
			deQueue(cQ);
			break;
		case 'p': 
        case 'P':
			printQ(cQ);
			break;
		case 'b': 
        case 'B':
			debugQ(cQ);
			break;
		case 'q': 
        case 'Q':
            freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue() {
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ) {
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

element getElement() {
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/**
 * @brief 
 * 
 * 큐의 경우 front 와 rear가 같은 경우 비어있다. 
 * 
 * @param cQ 비어있는지 확인할 큐
 * @return int 비어있으면 1, 안비어있으면 0 
 */
int isEmpty(QueueType *cQ) {
    if (cQ->front == cQ->rear){
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;
}

/**
 * @brief 
 * 
 * 원형큐의 경우 front 와 rear사이에 하나의 공간을 남겨두는데 그 이유가 empty와 full 의 상태를 따로 구분을 하기 위해서이다.. 
 * 그렇기 때문에 하나의 빈공간을 고려해서 rear에 하나가 추가된 위치(rear+1%큐크기)가 front 인걸 확인해봄으로써 체크할 수 있다.
 * 
 * @param cQ 가득 차 있는지 확인할 큐
 * @return int 가득 차 있으면 1, 넣을 공간이 더 있으면 0을 리턴해준다.
 */
int isFull(QueueType *cQ) {
    if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;
}


/**
 * @brief 
 * 
 * 큐가 가득 차 있는 경우에는 추가해줄 수가 없으니까 넣지말고 리턴해준다.
 * else 문은 빼는게 더 좋아보인다.
 * 큐는 rear에 값을 넣어주니 rear의 값을 하나 옮겨준 뒤
 * 그 위치에 넣을 값을 넣어준다.
 * 
 * @param cQ 아이템을 넣어줄 큐
 * @param item 넣을 아이템
 */
void enQueue(QueueType *cQ, element item) {
    
    if(isFull(cQ)) return;
	
    cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
    cQ->queue[cQ->rear] = item;
}

/**
 * @brief 
 * 
 * 큐가 비어있을 경우에는 빼줄 값이 없으니까 빼지말라고 리턴해준다.
 * 큐는 앞에서부터 값을 빼주지만 현재의 알고리즘으로 보아 fron는 언제나 비워주게 설정되어 있기 때문에 front에 1을 더한 위치의 값을 옮겨준다. 
 * 추가적으로 위치를 옮겨주지만 말고 ' '로 바꿔준다.
 * 
 * @param cQ 아이템을 뺴줄 큐
 */
void deQueue(QueueType *cQ) {
    if(isEmpty(cQ)) return;

    cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;
    cQ->queue[cQ->front] = ' ';	
}


void printQ(QueueType *cQ) {
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) {

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

