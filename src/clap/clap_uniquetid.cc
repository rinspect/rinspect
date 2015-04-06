#include "clap_uniquetid.hh"

class ThreadNode {
public:
  pthread_t thr;
  int id;
  ThreadNode* parent;
  vector<ThreadNode*> children;
};

class ThreadTree {
  ThreadNode *root;
  map<pthread_t,ThreadNode*> pthread_to_node;

public:

  ThreadTree() {
    root = NULL;
  }

  ThreadNode* find_node(pthread_t this_thr) {
    map<pthread_t,ThreadNode*>::iterator it = pthread_to_node.find(this_thr);
    if (it != pthread_to_node.end()) 
      return it->second;
    else
      return NULL;
  }

  ThreadNode* add_root_node(pthread_t this_thr) {
    ThreadNode* n = new ThreadNode;
    pthread_to_node[this_thr] = n;
    n->thr = this_thr;
    n->id = 1;
    n->parent = 0;
    root = n;
    return n;
  }

  ThreadNode* add_child_node(pthread_t this_thr, ThreadNode* m) {
    assert( m != NULL );
    ThreadNode* n = new ThreadNode;
    pthread_to_node[this_thr] = n;
    n->thr = this_thr;
    n->id =  m->children.size() + 1;
    n->parent = m;
    m->children.push_back(n);
    return n;
  }

  ThreadNode* add_node(pthread_t this_thr, pthread_t parent_thr) {
    ThreadNode* n = find_node(this_thr);
    if (n != NULL) return n;

    // this thread has not been added before
    ThreadNode* m = find_node(parent_thr);
    if (m == NULL) {
      assert( root == NULL);
      return add_root_node(this_thr);
    }
    
    // this is a child thread
    return add_child_node(this_thr, m);
  }

  int get_tid(pthread_t this_thr) {
    ThreadNode* n = find_node(this_thr);
    
    if (root == NULL) {
      n = add_root_node(this_thr);
    }

    assert(n);
    int tid = n->id;


    int count_level = 1;

    while (n->parent != NULL) {
      n = n->parent;
      tid = tid*100 + n->id;
      count_level ++;
    }

    assert(count_level <= 4);

    return tid;
  }

};

ThreadTree *thread_tree = NULL;

void unique_thread_add(pthread_t this_thr, pthread_t parent_thr)
{
  if (thread_tree == NULL) 
    thread_tree = new ThreadTree();
  thread_tree->add_node(this_thr,parent_thr);
}

map<long, int>* tids;
int unique_thread_get_tid(pthread_t this_thr)
{
//	if(tids==NULL) tids=new map<long,int>;
////	std::cout<<(*tids).size()<<std::endl;
//	if((*tids).find(this_thr)==(*tids).end())
//	{
////		std::cout<<(*tids).size()<<std::endl;
//		(*tids)[this_thr]=(*tids).size();
//	}
//	std::cout<<(*tids)[this_thr]<<std::endl;
//	std::cout<<(*tids).size()<<std::endl;


//	return (*tids)[this_thr];
  if (thread_tree == NULL)
    thread_tree = new ThreadTree();
  int res = thread_tree->get_tid(this_thr);
  return res;
}
void remove_tid(){
//	cout<<(*tids).size()<<endl;
	(*tids).erase(pthread_self());
//	cout<<(*tids).size()<<endl;
}



map<char*,int> *obj_table = NULL;

int unique_obj_get_id(char *ptr)
{
  int res = 0;

  if (obj_table == NULL)
    obj_table = new map<char*,int>;

  if (ptr) {
    map<char*,int>::iterator it = obj_table->find(ptr);
    if (it != obj_table->end())
      res = it->second;
    else {
      res = obj_table->size()+1;
      (*obj_table)[ptr] = res;
    }
  }

  return res;
}
