#include "dlist.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const string member[] = {"regular", "silver", "gold", "platinum"};
const int MEMTYPE = 4;

struct caller
{
    string name;    // caller's anme
    int timeStamp;  // the tick calling in
    int status;     // index for membertype string in MEMBER
    int duration;   // call duration
};

int main(){
    Dlist<caller> listRegu, listSilv, listGold, listPlat;   // four queues for answering
    Dlist<caller> listTotal;                                // one queue for calling
    int entry;      // total number of caller
    cin >> entry;

    // initialize all the callers in four queues from cin
    for (int i = 0; i < entry; i++){
        
        string input;
        
        // customer is the god
        caller *god1 = new caller;  // for answering queues
        caller *god2 = new caller;  // for calling queue

        cin >> input;
        god1->timeStamp = god2->timeStamp = atoi(&input[0]);
        input.clear();

        cin >> input;
        god1->name = god2->name = input;
        input.clear();
        
        cin >> input;
        // search for the status in MEMBER
        for (int i = 0; i < MEMTYPE; i++)
            if (member[i] == input)
                god1->status = god2->status = i;
        input.clear();

        cin >> input;
        god1->duration = god2->duration = atoi(&input[0]);
        input.clear();

        listTotal.insertFront(god2);
        switch (god1->status)
        {
        case 0:
            listRegu.insertFront(god1);
            break;
        
        case 1:
            listSilv.insertFront(god1);
            break;

        case 2:
            listGold.insertFront(god1);
            break;

        case 3:
            listPlat.insertFront(god1);
            break;

        default:
            break;
        }

    }

    // Simulation begins
    int service = 1;    // the ticks left to finish the current service
    int tick = 0;       // the current tick
    // the loop works when either callers are waiting or the service is going on
    while ((!listRegu.isEmpty() || !listSilv.isEmpty() ||
         !listGold.isEmpty() || !listPlat.isEmpty()) || (service > 0)) {
             
        cout << "Starting tick #" << tick << endl;

        // print the calling in information for current tick
        // by checking the last-in-queue's timeStamp
        while (!listTotal.isEmpty()) {
            caller *temp = listTotal.removeBack();
            if (temp->timeStamp == tick) {
                cout << "Call from " << temp->name << " a "
                        << member[temp->status] << " member" << endl;
                delete temp;
            } else {
                listTotal.insertBack(temp);
                break;
            }
        }
        
        // tick increases before check value of SERVICE
        // because the part behind might be skipped
        tick++;
        // SERVICE decreases each tick
        // if positive, the service is going on
        // skip the part behind
        if (--service > 0) continue;
        // if service == 0, choose a new caller to answer
        // as long as there are non-empty answering queues.
        if (!listRegu.isEmpty() || !listSilv.isEmpty() ||
         !listGold.isEmpty() || !listPlat.isEmpty()){
            
            // customer is the god
            caller *god;
            bool isfound = 0;

            // From platinum to regular members, 
            // see if the first caller in each queue has timestamp equals to current tick
            
            // Because tick increases after calling in is finished,
            // here the value of tick is bigger by 1.
            if (!listPlat.isEmpty() && !isfound){
                god = listPlat.removeBack(); 
                if (god->timeStamp >= tick){listPlat.insertBack(god);}
                else {isfound = 1;}
            }
            if (!listGold.isEmpty() && !isfound){
                god = listGold.removeBack(); 
                if (god->timeStamp >= tick){listGold.insertBack(god);}
                else {isfound = 1;}
            }
            if (!listSilv.isEmpty() && !isfound){
                god = listSilv.removeBack();
                if (god->timeStamp >= tick){listSilv.insertBack(god);} 
                else {isfound = 1;}
            }
            if (!listRegu.isEmpty() && !isfound){
                god = listRegu.removeBack();
                if (god->timeStamp >= tick) {listRegu.insertBack(god);}
                else {isfound = 1;}
            }
				
			if (isfound){
				service = god->duration;    // refresh the ticks left for finishing the current service.
				cout << "Answering call from " << god->name << endl;
				delete god;
			}
        }
    }

    return 0;
}