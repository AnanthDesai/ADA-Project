
#include<iostream>
#include<stdlib.h>
#include<string>
#include<iomanip>
#include<time.h>
#include<ctime>


#define MAX 9999

 using namespace std;

 int **graph;
 int police_count = 0, med_count = 0, fire_count = 0, org_count = 0, home_count = 0;        //COUNT

 typedef class Node{            // Main class of the node : Represents the type of location

     public:
        int number;             // Node number
        char type;              // Type of node
        char bl_type;           // Blood group
        Node *next;             // Next node


        Node(int num, char typ){        //Constructor initializing the values of the node
            number = num;
            type = typ;
            next = NULL;
        }
        Node(){
            number = 0;
            type = '$';
        }
        int display_number(){
            cout<<number;
            return 0;
        }
        int display_type(){
            cout<<type;
            return 0;
        }
        int display(){
            display_number();
            cout<<"\t\t";
            display_type();
            cout<<endl;
            return 0;
        }
};

Node* start = NULL;
Node* last = NULL;


 int get_graph(int dimension){              // INPUT ADJACENCY MATRIX

    // Dynamic memory allocation of 2d array;
    graph = (int**)malloc(dimension * sizeof(int*));

    for(int i=0;i<dimension;i++)
        graph[i] = (int*)malloc(dimension * sizeof(int));

    cout<<"Enter the distance between the following locations   (9999 for nodes not connected): "<<endl;

    for(int i=0;i<dimension;i++)
        for(int j=i+1;j<dimension;j++){
            cout<<"Node "<<i+1<<" to Node "<<j+1<<" : ";
                cin>>graph[i][j];
            graph[j][i]=graph[i][j];
        }
    for(int i=0, j=0; i<dimension, j<dimension; i++,j++)
        graph[i][j] = 0;

    return 0;
 }

 int put_graph(){                   //OUTPUT ADJACENCY MATRIX
    int dimension = last->number;
    Node* temp=start;
    cout<<"Node\t";
    for(int i=0;i<dimension;i++){
        cout<<temp->type<<"\t";
        temp=temp->next;
    }
    temp=start;
    cout<<endl<<endl;
    for(int i=0;i<dimension;i++){
        cout<<temp->type<<"\t";
        for(int j=0;j<dimension;j++)
            if(graph[i][j]!=9999)
                cout<<graph[i][j]<<"\t";
            else
                cout<<"-"<<"\t";
        cout<<endl;
        temp=temp->next;
    }
    temp = NULL;
    delete temp;
    return 0;
 }

 int count_update(char node_type){          // Updating the number of service points available

    switch(node_type){
        case 'P':
        case 'p': police_count++;
                    break;
        case 'm':
        case 'M': med_count++;
                    break;
        case 'f':
        case 'F': fire_count++;
                    break;
        case 'h':
        case 'H': home_count++;
                    break;

        case 'o':
        case 'O': org_count++;
                    break;

        default: cout<<"Not a valid type. Enter  again."<<endl;
                    return 0;
    }
    return 1;
 }

 int show_info(){           /*  DISPLAY THE GRAPH INFO  */
    Node* temp = start;
    cout<<endl<<endl<<"Node\tType"<<endl;
    for(int i = 0;i<last->number, temp!=NULL; i++){
        cout<<i+1<<"\t"<<temp->type<<endl;
        temp=temp->next;
    }
    cout<<"Number of Police Stations\t:\t"<<police_count<<endl;
    cout<<"Number of Hospitals\t\t:\t"<<med_count<<endl;
    cout<<"Number of Fire Stations\t\t:\t"<<fire_count<<endl;
    cout<<"Number of Houses\t\t:\t"<<home_count<<endl;
    cout<<endl;
    return 0;
}

int input_graph(){                      //Input initial graph
    int num_of_nodes;
    char node_type;
    cout<<"Enter the number of nodes: ";
        cin>>num_of_nodes;
    for(int i=0;i<num_of_nodes;i++){
        goto again;
        again:
        cout<<"Enter the type of node "<<i+1<<": ";
            cin>>node_type;
            int n = count_update(node_type);
            if(n==0)
                goto again;
        Node *node =new Node(i+1,node_type);
       if(start==NULL){
            start=last=node;
        }
        else{
            last->next=node;
            last=last->next;
       }
    }
    get_graph(num_of_nodes);            //Input initial adjacency matrix
    return 0;
}


//INCREASE THE SIZE OF THE GRAPH
int increase_graph(){                   //UPDATE THE GRAPH WITH INCREASED SIZE
    int temp_graph[last->number][last->number];
    for(int i=0;i<last->number;i++)
        for(int j=0;j<last->number;j++)
            temp_graph[i][j] = graph[i][j];

    delete graph;

     // Dynamic memory allocation of 2d array;
    graph = (int**)malloc((last->number+1)* sizeof(int*));

    for(int i=0;i<last->number+1;i++)
        graph[i] = (int*)malloc((last->number+1) * sizeof(int));

    for(int i=0;i<last->number;i++)
        for(int j=0;j<last->number;j++)
            graph[i][j]=temp_graph[i][j];

    return 0;
}

int add_graph(){            // INPUT THE ELEMENTS OF THE UPDATED GRAPH
    increase_graph();
    char typ;
again1:
    cout<<"Enter the type of node "<<last->number+1<<" : ";
        cin>>typ;
    int n = count_update(typ);
    if(n==0)
        goto again1;
    Node* node = new Node(last->number+1,typ);
    last->next = node;
    last = last->next;
    cout<<"Enter the distance between the following locations   (9999 for nodes not connected): "<<endl;
    for(int i=0;i<last->number-1;i++){
        cout<<"Node "<<last->number<<" to Node "<<i+1<<" : ";
            cin>>graph[last->number-1][i];
            graph[i][last->number-1] = graph[last->number-1][i];
    }
    graph[last->number-1][last->number-1] = 0;
    return 0;
}


//DISPLAY THE SHORTEST PATH
void put_path(int path[], int dest_node){
    if(path[dest_node]==-1)
        return;

    put_path(path, path[dest_node]);
        cout<<" <- "<<dest_node+1;
}

int chooseVertex(int distance[], int visited_array[]){      /*  CHOOSES THE NEXT MIN WEIGHT VERTEX   */
    int min_node;
    int  min_dist = MAX;
    for(int i=0;i<last->number;i++)
        if(visited_array[i]==0 && distance[i] <= min_dist){
            min_dist = distance[i];
            min_node = i;
    }
    return min_node;
}

int chooseService(int distance[], int path[] , char node_type, int node_req){
    Node* temp = start;
    int dist[last->number],min_node,k=0, min_dist = MAX;
    for(int i=0;i<last->number, temp!=NULL; i++){
        if(((int)temp->type==(int)node_type) || ((int)temp->type==(int)node_type+32)){      // CHOOSE THE APPROPRIATE SERVICE FROM ALL THE SHORTEST
            dist[k] = distance[i];
            if(dist[k]<min_dist){
                min_dist = dist[k];
                min_node = temp->number;
            }
            k++;
        }
        temp=temp->next;
    }
    cout<<endl<<"The fastest service is given by node "<<min_node<<" in the following route: "<<endl<<node_req;
        put_path(path,k-1);
        cout<<"\b"<<min_node;
    return min_dist;
}


int Dijkstra(int node_req, char node_type){
    int distance[last->number];     //ARRAY WHICH HOLDS THE DISTANCE TO ALL THE NODES OF THE SAME TYPE
    int visited_array[last->number];        // ARRAY WHICH HOLD THE VISITED NODES
    int path[last->number];     //HOLDS THE PATH TO THE SHORTEST ROUTE

    float start_time = clock();


    for(int i=0;i<last->number;i++){        //INITIALIZE THE ARRAY VALUES: DIST TO INFINITY AND VISITED ALL TO ZERO
        distance[i] = MAX;
        visited_array[i] = 0;
        path[i]=-1;
    }
      path[0]=-1;     //SOURCE NODE
    distance[node_req-1] = 0;       // SET SOURCE DIST ZERO

    for(int i=0;i<last->number-1;i++){
        int k = chooseVertex(distance, visited_array);

        visited_array[k] = 1;

        for(int j=0;j<last->number;j++)
            if(!visited_array[j] && graph[k][j]  && distance[j]>( distance[k] + graph[k][j] )){
                 path[j] = k;
                distance[j] = distance[k] + graph[k][j];
            }
    }

    float end_time = clock();
    float time_taken = (start_time + end_time)/CLOCKS_PER_SEC;

    cout<<endl<<endl;
    distance[0] = chooseService(distance, path, node_type, node_req);
    cout<<endl<<" and it is "<<distance[0]<<" units away from your location."<<endl;

    cout<<"Start time: "<<start_time<<endl<<"End time: "<<end_time<<endl<<"Time taken to produce result: "<<time_taken<<endl<<endl;
    return 0;
}

int Emergency(char node_type){
    int node_req;
    cout<<endl<<"Enter the node at which service is required: ";
        cin>>node_req;
    if(node_req>last->number)
        cout<<"Location not present on the graph. Please try again."<<endl;
    else{
        Dijkstra(node_req,node_type);
    }
    return 0;
}

int Organ_Emergency(){
    Node *temp = start;
    int node_req;
again2:
    cout<<"Enter the source hospital from the following list of hospitals: "<<endl;
    cout<<"Type\tNode"<<endl;
    while(temp!=NULL){
        if(temp->type=='M'|| temp->type=='m')
            cout<<temp->type<<"\t"<<temp->number<<endl;
            temp=temp->next;
    }
    cin>>node_req;
    temp=start;
    while(temp!=NULL){
        if(temp->number==node_req){
            Dijkstra(node_req,'M');
            break;
        }
        else
            temp=temp->next;
    }
    if(temp==NULL){
        cout<<"Source is not a hospital! Please enter again."<<endl;
        goto again2;
    }
    temp==NULL;
    delete temp;
    return 0;
}

int delete_node(int node_num){
    int u=0,v=0;
    int temp_graph[last->number][last->number];
    for(int i=0;i<last->number;i++)
        for(int j=0;j<last->number;j++)
            temp_graph[i][j] = graph[i][j];

    delete graph;

     // Dynamic memory allocation of 2d array;
    graph = (int**)malloc((last->number-1)* sizeof(int*));

    for(int i=0;i<last->number-1;i++)
        graph[i] = (int*)malloc((last->number-1) * sizeof(int));

    for(int i=0;i<last->number;i++){
         v=0;
        for(int j=0;j<last->number;j++){
            if(i==node_num-1){
                i++;
            }
            if(j==node_num-1){
                j++;
            }
                graph[u][v] = temp_graph[i][j];
                v++;
        }
        u++;
    }
    return 0;
}

int remove_graph(){
    int node_num;
    cout<<"Enter the node you want to remove: ";
        cin>>node_num;
    delete_node(node_num);          // UPDATES THE GRAPH AFTER DELETING THE ROW AND COLUMN
    Node* temp2 = start;            // UPDATION OF THE LINKED LIST
    Node* temp1;
    temp1 = temp2->next;
    if(temp2->number==node_num){        //STARING ELEMENT IS THE DELETED ELEMENT CONDITION
        start = temp1;
        temp2->next = NULL;
        delete temp2;
    }
    else{
        while(temp1!=NULL){
            if(temp1->number==node_num){
                temp2->next = temp1->next;
                temp1->next = NULL;
                delete temp1;
                break;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    temp1 = start;
    while(temp1!=NULL){
        if(temp1->number>node_num){
            temp1->number--;
        }
        temp1 = temp1->next;
    }
    cout<<"\n"<<"Node "<<node_num<<" deleted succesfully!!\n";
    return 0;
}

int choice_entry(){
    int n;

    cout<<endl<<endl;
    cout<<"1. Codes:"<<endl<<"\t Police emergency: \t  100"<<endl<<"\t Medical emergency: \t 108"<<endl<<"\t Fire emergency: \t 104"<<endl<<"\t Organ Transplant: \t 110"<<endl;
    cout<<"2. Show the present graph."<<endl;
    cout<<"3. Add an element to the present graph"<<endl;
    cout<<"4. Delete a node from the graph."<<endl;
    cout<<"5. Show Graph info."<<endl;
    cout<<"6. Quit"<<endl<<endl;
    cout<<"Enter your choice/code: ";
          cin>>n;
    return n;
}

int welcome(){
    for(int i=0;i<73;i++)
        cout<<"*";
    cout<<endl;
    cout<<"*"<<"\t\t"<<"WELCOME TO EMERGENCY SERVICE PROVISION SYSTEM"<<"\t\t"<<"*"<<endl;
    for(int i=0;i<73;i++)
        cout<<"*";
    cout<<endl<<endl;
    return 0;
}


int main(){
    welcome();
    input_graph();
    int choice;
    do{
        choice = choice_entry();
        switch(choice){
            case 2: put_graph();
                    break;
            case 3: add_graph();
                    break;
            case 4: remove_graph();
                    break;
            case 5: show_info();
                    break;
            case 6: exit(0);
                    break;
            case 100:  if(police_count>0)
                            Emergency('P');
                        else
                            cout<<"No Police stations on the grid.";
                        break;
            case 108: if(med_count>0)
                            Emergency('M');
                        else
                            cout<<"No Hospitals on the grid.";
                        break;
            case 104: if(fire_count>0)
                            Emergency('F');
                        else
                            cout<<"No Fire Stations on the grid.";
                        break;
            case 110: if(med_count>1)
                            Organ_Emergency();
                        else
                            cout<<"Only one/none hospital available on the grid.";
                       break;
            default: cout<<"Not a Valid choice!"<<endl;
                    break;
        }
    }while(choice!=6);
    return 0;
}
