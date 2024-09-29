/* Siva Reddy Gangireddy
 * September 2024
 * FIFO Queue using circular buffer
 * Circular buffer has FRONT and REAR pointers.
 *   FRONT ---> points to the element added at first to the buffer
 *   REAR ----> pointst to the most recent element added to buffer
 * 
 * 
 * This FIFO Queue holds the pointers to the audio buffers.
 * The Audio buffer is defined as a struct consists of pointers to the audio samples
 * and the number of audio samples.
 * 
 * Since the FIFO Queue is implemented is circular buffer, when the Queue is full, it overwrites
 * 
 * 
 * The FIFO queue functions
 *   enqueue(AudioBuffer *audio_buffer)
 *      Adds the audio buffer pointers to the Queue
 *   
 *   dequeue()
 *      removes the a pointer to the audio buffer which was added first to the Queue. 
 *   
 *   TopofQueue()
 *      Returns a pointer to the audio buffer which was added first to the Queue.
 * 
 *   EndofQueue()
 *      Returns a pointer to audio buffer which was added most recently.
 * 
 *   isEmpty()
 *      Checks whether the Queue is empty or not. If yes returns TRUE.
 * 
 *   isFull()
 *      Checks whether the Queue is full or not. If yes, returns TRUE.
 * 
 *   
 * */

#include <iostream> // input and output
#include <vector> //to define a vector data structure
#include <stdexcept>

using namespace std;

struct AudioBuffer
{
    //vector<double> audio_samples;
    void *samples;
    int num_samples; //number sampels in each buffer
};

class CyclicQueue{
    public:
        vector<AudioBuffer*> q; // A vector that stores the pointers to the audio buffers
        int size; //size of the Circular queue. Its fixed. When the 
        int front; //points to the front of the Queue
        int rear; //points to the rear of the 
    
        //A constructor to initialize the variables
        //When an object is created these will be inititalised automatically
        CyclicQueue(int k){
            size = k;
            q.resize(size);
            //when the circular queue is empty both are point to -1
            front = -1;
            rear= -1;
        }

        void enqueue(AudioBuffer *audio_buffer){
            // Adds an audio buffer pointer to the Queue
            //if the Queue is full overwrites the data, by changing the REAR to 0

            AudioBuffer *qtop;

            try{
                if(!isFull()){
                    //if the Queue is empty
                    if (isEmpty()){
                        front =0;
                        rear = 0;
                    }
                    //to maintain the circular condition
                    else if(rear == size-1){
                        rear = 0;
                    }
                    //normal case
                    else{
                        rear += 1;
                    }
                    q[rear] = audio_buffer;
                }
                else{
                    throw ("Queue Full Error");
                }
            }
            catch(...){
                cout<<"The Queue is Full overwrting the data."<<"\n";

                //Circular queue is full. So checks two conditions to enequeue
                //next pointer
                if((front==0 && rear == size-1)){
                    qtop = dequeue();
                    rear = 0;
                }
                else if(rear == front-1){
                    qtop = dequeue();
                    rear +=1;
                }

                q[rear] = audio_buffer;
            }
            return;
        } 


        AudioBuffer *dequeue(){
            //Returns a pointer to an audio buffer which was added first to the Queue.
            //If the Queue is empty. It was handled through an exception module
            try{
                if(!(isEmpty())){
                    //if there is only one element. After deQueue the Queue will be empty

                    AudioBuffer *qtop = q[front];

                    if (rear == front){
                        front = -1;
                        rear = -1;
                    }
                    //to maintain the circular condition
                    else if (front == size-1){
                        front = 0;
                    }
                    //normal case
                    else{
                        front +=1;
                    }
                    return qtop;
                }
                else{
                    throw out_of_range("QueueEmpty Error") ;
                }
            }
            catch(...){
                cout <<"the Queue is empty"<<"\n";
                return NULL;
            }
        }            

        AudioBuffer *TopOfQuue(){
            //Returns the pointer which was added to the first to the circualr queue.

            if (isEmpty()){
                cout <<"the queue is empty. No top of queue"<<"\n";
                return NULL;
            }

            return q[front];
        }
        
        AudioBuffer *EndOfQueue(){
            //Returns a pointer which was added most recentnly to the circular queue.

            if (isEmpty()){
                cout <<"the queue is empty. No end element of queue"<<"\n";
                return NULL;
            }

            return q[rear];
        }

        bool isEmpty(){
            //Returns true of the circular queue is empty

            if (front == -1){
                return 1;
            }
            else return 0;
        }

        bool isFull(){
            //returns true of the circular queue is full

            if ((front == 0 && rear == size -1) || (rear == front-1)){
                return 1;
            }
            else{
                return 0;
            }
        }
};

// writng class member functions outside of class defination.
/* bool CyclicQueue::isEmpty2(){
    //Returns true of the circular queue is empty

    if (front == -1){
        return 1;
    }
    else return 0;

} */

int main(){
    /*Below test cases are written based on this value. 
    * But this can be changed as required
    */
    int buffer_size = 3; 

    //audio buffer struct declaration
    AudioBuffer audio_buffer1;
    AudioBuffer audio_buffer2;
    AudioBuffer audio_buffer3;
    AudioBuffer audio_buffer4;
    AudioBuffer audio_buffer5;

    //Declaration of pointers to the audio buffers
    AudioBuffer *Buffer1 = &audio_buffer1;
    AudioBuffer *Buffer2 = &audio_buffer2;
    AudioBuffer *Buffer3 = &audio_buffer3;
    AudioBuffer *Buffer4 = &audio_buffer4;
    AudioBuffer *Buffer5 = &audio_buffer5;

    //Circurlar queue intialisation
    CyclicQueue *myQueue = new CyclicQueue(buffer_size);

    /*test case 1:
    * Checks the circular property of the queue
    *
    * In this case if the circual queue is full
    *     front = 0 and rear = size-1
    *     Since the queue is circular. it overwrites the data
    *       front = 1 and rear = 0
    */

    //Enqueue
    /*
    * At index 0, Buffer1
    * At index 1, Buffer2
    * At index 2, Buffer3
    * The Queue is full at this point
    * FRONT = 0, REAR=2
    */
    cout <<"##### Enqueue ##########"<<"\n";
    myQueue->enqueue(Buffer1);
    myQueue->enqueue(Buffer2);
    myQueue->enqueue(Buffer3); //at this point circular buffer is full
    cout<<"Front and rear: "<<myQueue->front<<" "<<myQueue->rear<<"\n"; //front =0, rear=2

    /*
    * Since the Queue is full at this point
    * isFull() should return 
    */
    bool full = myQueue->isFull();
    if (full){
        cout<<"the Queue is full"<<"\n";
    }else{
        cout<<"the Queue is not full"<<"\n";
    }
    //property of circular buffer
    /*
    * Since the Queue is implemented with a circular buffer
    * Enqueue will overwrite the exisitng data in the queue
    * So in the first enqueue, rear=0, front=1
    * In the second enqueue, rear=1, front=2
    */
    myQueue->enqueue(Buffer4);
    myQueue->enqueue(Buffer5);
    cout<<"Front and rear: "<<myQueue->front<<" "<<myQueue->rear<<"\n"; //front=2, rear=1

    //Dequeue
    /*
    * Now the queue is full and dequeue all the data in the Queue 
    * 
    */
    cout <<"##### Dequeue ##########"<<"\n";
    AudioBuffer *x;
    x = myQueue->dequeue(); //front= 0, rear=1
    x = myQueue->dequeue(); //front = 1, rear=1
    x = myQueue->dequeue(); // the Queue is empty at this point. front=-1, rear=-1
    cout<<"Front and rear: "<<myQueue->front<<" "<<myQueue->rear<<"\n"; //front=-1, rear=-1

    /* Check for Queue Empty
    * Since there are no elements in the Queue, the isEmpty should return True
    */
    bool empty = myQueue->isEmpty();
    if (empty){
        cout<<"the Queue is empty"<<"\n";
    }else{
        cout<<"the Queue is not empty"<<"\n";
    }
    cout<<myQueue->TopOfQuue()<<"\n";

 /*    //myQueue->dequeue();
    //myQueue->dequeue();
    //cout<<myQueue->isEmpty()<<"\n";
    myQueue->enqueue(Buffer3);
    cout<<myQueue->front<<" "<<myQueue->rear<<"\n";
    //cout<<myQueue->front<<" "<<myQueue->rear<<"\n";
    
    //cout<<myQueue->isEmpty()<<"\n";
    //cout<<myQueue->isFull()<<"\n";

    cout<<myQueue->TopOfQuue()<<" "<<Buffer2<<"\n";

    cout<<myQueue->EndOfQueue()<<" "<<Buffer3<<"\n";
 */
    delete myQueue;
    return 0;

}