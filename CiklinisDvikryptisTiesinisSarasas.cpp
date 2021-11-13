#include <iostream>

using namespace std;

struct node
{
  node *next;
  node *prev;
  int data;
};

class List
{
  private:
  node *tail;
  int count;

  public:
  List()
  {
    tail=NULL;
    count=0;
  }
  
  ~List()
  {
  	if(!IsEmpty())
  	{
  		node *temp=tail;
	  	while(temp->prev!=tail)
	  	{
	  		node *n=temp;
	  		temp=temp->prev;
		  	delete n;
		}
		delete temp;
	}
  }

  bool IsEmpty()
  {
    return tail==NULL;
  }
  
  void AddNodeEnd(int data)
  {
    node *newnode;
    newnode=new node;
    newnode->data=data;
    
	newnode->next=tail->next;
	newnode->prev=tail;
	tail->next->prev=newnode;
	tail->next=newnode;
	tail=newnode;
    count++;
  }

  void AddNodeStart(int data)
  {
    node *newnode;
    newnode=new node;
    newnode->data=data;
    
	newnode->next=tail->next;
	newnode->prev=tail;
	tail->next->prev=newnode;
	tail->next=newnode;
    count++;
  }
  
  void AddNodePos(int pos, int data)
  {
    node *newnode;
    newnode=new node;
    newnode->data=data;
    
    node *pre=tail;
    node *cur=tail->next;
    for(int i=1;i<pos;i++)
    {
      pre=cur;
      cur=cur->next;
    }
    newnode->next=cur;
    newnode->prev=pre;
    pre->next=newnode;
    cur->prev=newnode;
    count++;
  }
  
  void AddNodeEmpty(int data)
  {
  	node *newnode;
    newnode=new node;
    newnode->data=data;
    
	newnode->next=newnode;
	newnode->prev=newnode;
	tail=newnode;
	count++;
  }

  void AddNode(int pos, int data)
  {
    if(IsEmpty())
    {
    	if(pos==1)
    		AddNodeEmpty(data);
    	else cout<<"pozicija uz ribu"<<endl;
    }
    else
    {
    	if(pos==count+1)
    		AddNodeEnd(data);
    	else if(pos==1)
    		AddNodeStart(data);
    	else if(pos>1&&pos<=count)
    		AddNodePos(pos,data);
    	else
    		cout<<"pozicija uz ribu"<<endl;
	}
  }
  
  int DeleteNodeEnd()
  {
    int deleted = tail->data;
    count--;
    if(tail->next==tail)
    {
        delete tail;
        tail=NULL;
	    cout<<"istrintas elementas yra "<<deleted<<endl;
        return deleted;
    }
    else
    {
        tail->prev->next=tail->next;
        tail->next->prev=tail->prev;
        node *temp=tail->prev;
        delete tail;
        tail=temp;
        cout<<"istrintas elementas yra "<<deleted<<endl;
        return deleted;
    }
  }

  int DeleteNodeStart()
  {
    count--;
    int deleted = tail->next->data;
    if(tail->next==tail)
    {
        delete tail;
        tail=NULL;
	    cout<<"istrintas elementas yra "<<deleted<<endl;
        return deleted;
    }
    else
    {
        node *temp=tail->next;
        tail->next=tail->next->next;
        temp->next->prev=tail;
        delete temp;
	    cout<<"istrintas elementas yra "<<deleted<<endl;
        return deleted;
    }
  }
  
  int DeleteNodePos(int pos)
  {
  	count--;
    if(tail->next==tail)
    {
		int deleted = tail->next->data;
        delete tail;
        tail=NULL;
        cout<<"istrintas elementas yra "<<deleted<<endl;
        return deleted;
    }
    else
    {
        node *pre=tail;
        node *cur=tail->next;
        for(int i=1;i<pos;i++)
        {
          pre=cur;
          cur=cur->next;
        }
        pre->next=cur->next;
        cur->next->prev=pre;
        int deleted = cur->data;
        delete cur;
        cout<<"istrintas elementas yra "<<deleted<<endl;
        return deleted;
    }
  }
  
  int DeleteNode(int pos)
  {
  	if(IsEmpty())
    {
		cout<<"Sarasas tuscias!!!"<<endl;
    }
    else
    {
    	if(pos==count)
    		DeleteNodeEnd();
    	else if(pos==1)
    		DeleteNodeStart();
    	else if(pos>1&&pos<count)
    		DeleteNodePos(pos);
    	else
    		cout<<"pozicija uz ribu"<<endl;
	}
  }
  
  void Display()
  {
    if(!IsEmpty())
    {
      node *temp=tail->next;
      do
      {
        cout<<temp->data<<' ';
        temp=temp->next;
      }while(temp!=tail->next);
      cout<<endl;
    }
    else
    {
      cout<<"Sarasas tuscias"<<endl;
    }
  }

  void Reverse()
  {
  	if(!IsEmpty())
  	{
  		if(!(tail->next==tail))
  		{
  			node *cur=tail->next;
  			node *head=tail->next;
  			node *pre;
  			do
  			{
  				pre=cur->prev;
  				cur->prev=cur->next;
  				cur->next=pre;
  				cur=cur->prev;
			}while(cur!=head);
			tail=cur;
		}
		cout<<"Sarasas apsuktas"<<endl;
	}
	else cout<<"Sarasas tuscias"<<endl;
  }
  
  int Search(int value)
  {
    if(!IsEmpty())
    {
      node *temp=tail->next;
      int pos=1;
      do
      {
        if(temp->data==value)
        {
        	cout<<"ieskomo skaiciaus pozicija - "<<pos<<endl;
          return pos;
        }
        pos++;
        temp=temp->next;
      }while(temp!=tail->next);
    }
    cout<<"skaicius "<<value<<" nerastas sarase"<<endl;
    return -1;
  }
};

int main()
{
  List list;
  char t=' ';
  int value;
  cout<<"Ciklinis dvikryptis tiesinis sarasas"<<endl;
  while(t!='9')
  {
	cout<<"\nPasirink operacija ivesdamas skaiciu:"<<endl;
	cout<<"1.AddNode"<<endl;
	cout<<"2.DeleteNode"<<endl;
	cout<<"3.Search"<<endl;
	cout<<"4.IsEmpty"<<endl;
	cout<<"5.Display"<<endl;
	cout<<"6.Reverse"<<endl;
	cout<<"9.Exit"<<endl;
	
    cin>>t;
    system("cls");
    if(t=='1')
    {
	  int pos;
      cout<<"Ivesk pozicija, i kuria nori prideti: ";
      cin>>pos;
      cout<<"Ivesk skaiciu, kuri nori prideti: ";
      cin>>value;
      list.AddNode(pos,value);
    }
    else if(t=='2')
    {
      int pos;
      cout<<"Ivesk pozicija, is kurios nori pasalinti: ";
      cin>>pos;
      list.DeleteNode(pos);
    }
    else if(t=='3')
    {
    	cout<<"Ivesk ieskoma skaiciu: ";
    	cin>>value;
    	list.Search(value);
	}
	else if(t=='4')
    {
    	if(list.IsEmpty())
    		cout<<"Sarasas tuscias"<<endl;
		else
			cout<<"Sarasas netuscias"<<endl;
	}
    else if(t=='5')
    {
      cout<<"Sarasas: "<<endl;
      list.Display();
    }
    else if(t=='6')
    {
      list.Reverse();
    }
  }
}
