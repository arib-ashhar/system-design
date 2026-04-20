You are given a collection of computation units where each unit may require the results of other units before it can begin execution. 
Each unit produces an output that can be consumed by other units.

Your task is to design an execution engine that:
Determines a valid execution schedule such that every unit runs only after all the units it depends on have finished.
Maximizes concurrency by allowing independent units to execute parallely.
Ensures that outputs from prerequisite units are made available to dependent units at execution time.

Requirements:
1. Minimize the time
2. Get the order of th execution
3. Handle the cycle destection


Dsign paetten

1. Factory (work units)
2. composite design pattern
3. strategy ( to hande failure scenarios with different strategies)



Entities:
1. WorkUnit 
2. Edge
3. ExecutionUnit (WorkUnit)



getOrder: vector<ExecutionUnit>








[
	{"A" , "dep" : [] },
	{"B" , "dep" : ["A"]},
	{"C" , "dep" : ["A"]},
	{"D" , "dep" : ["B", "C", 'A']}
  E: dep A
]



A
	B
  	C
  		D
    
A B C D





class WorkUnit {
	private:
  	string name;
    int executionTime;
    vector<Edge*> edge;
  
    
};	


class ExecutionUnit {
	private:
		vector<WorkUnit*> workUnits;
    int timeStamp;
};

//directional
class Edge {
	private:
		WorkUnit* parent;
    WorkUnit* child;
  
};

class WorkUnitFactory {
	publlic:
		vector<WorkUnit*> createWorkUnits(sting input) {
    	// create list WorkUnit;
		}
};


class WorkEngine {
	private:
  	static WorkEgine* workeng;
    mutex mtx;
    WorkUnitFactory* wFac;
  publlic:
  	WorkEngin() {
    //initiliaze the factory
    }
		getWorkEngine() {
    	if(workeng == nullptr) {
      	mtx.lock()
        this->workeng = new WorkEngine();
        mtx.unlick()
        
      }
      else {
      	return this->workeng;
      }
    }
    
    process(stirng input) {
    	vector<WorkUnit*> workUnits = fac.createWorkUnits(input);
      //loop through each workUnit
      // find the order of executionUnit, time
      //incase these is
      // which all workTImes are in same timeStamp execute them aparalale
      // execute serial base ont he timestamp
      // Time for exectition is the maxTimStamp;
      
    }
    
    
};


class ExecutionEngine {
	private:
  	vector<vector<WorkUnit*>> graph;
    vector<int> inDeg
	public:
  /*
  A = A
  B = A -> B
  C = A -> C
  D = A -> B,C -> D
  
  
  */
  ExecutionEnging(vector<WorkUnit*> workUnits) {
  	int n = workUNits.size();
    graph.resize(n);
    // create graph;
    for(int i=0;i<n;i++) {
			for(int j=0;j<workUnit[i]->edges.size();j++) {
      	Edge = wokrUnit[i]->edge;
      	graph[WorkUnit[i]].push_back(edge->child);
      }
    }
  }
		vector<ExecutionUnit*> findTheOrder() {
    	// A
      // return ExecutionUnit(A);
      
      
      // B
      // 1
    	// do a topo sort
      // dfs or Kahn's algo
      
      
      //inDeg vector
      queue<pair<WorkUNit*, t>> q;
      for(auto: workUNits) {
      //if the indeg is 0
      	q.push(workUNit, 0);
      }
      
      vector<ExecutionUNit*> order;
      while(!q.empty()) {
      	int [u, t] = q.front(); q.pop();
				order.push_back(new ExecutionUnit(q, t));
        
        for(child: grph[u]) {
					inDeg[child]--;
          if(inDeg[child] == 0) {
          	q.push(child, t+1);
          }
        }
				
			}
      
      // inDeg of all the WorkUnits should 0
      // if any one of them is not zero then there is a cycle.
      
      
      // ignore the cyclic ones
      / And give me the order for the rest od them
      
      return order;
      
      
      
    
    }
    
    
};









