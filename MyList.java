
//https://repl.it/Flfp/0

class Node{
  private Object data;
  private Node next;
  
  public Node(){
    data = null;
    next = null;
  }
  
  public Node(Object data){
    this.data = data;
    this.next = null;
  }
  
  @Override
  public String toString(){
    return this.data.toString();
  }
  
  public void setNext(Node next){
    this.next = next;
  }
  
  public Node getNext(){
    return this.next;
  }
  
  public void setData(Object data){
    this.data = data;
  }
  
  public Object getData(){
    return this.data;
  }
}

class MyList{
  Node head = null;
  int count = 0;
  
  public void add(Object obj){
    if(head == null){
      head = new Node(obj);
    }
    else{
      Node node = getTail();
      node.setNext( new Node(obj) );
    }
    
    count++;
  }
  
  public void remove(int index){
    if(index >= 0 && index < count){
      Node temp = this.head;
      
      if(index == 0){
        this.head = head.getNext();
        count--;
        return;
      }
      
      // [0,1]->[1,2]-[2,null]
      int i = 0;
      Node previous = temp;
      while(temp.getNext() != null){
        
        if(i == index){
          break;
        }
        previous = temp;
        temp = temp.getNext();
        i++;
      }
      
      previous.setNext(temp.getNext());
      temp = null;
      count--;
    }
  }
  
  public Object get(int index){
    
    int i = 0;
    
    Node temp = head;
    
    while(temp != null){
      
      if(i == index){
        return temp.getData();
      }
      
      temp = temp.getNext();
      i++;
    }
    
    return null;
  }
  
  public void display(){
    
    Node temp = head;
    
    while(temp != null){
      
      System.out.println("\n " + temp);
      temp = temp.getNext();
      
    }
  }
  
  public boolean contains(Object obj){
    
    Node temp = head;
    
    while(temp != null){
      
      if(obj.equals(temp.getData())){
        return true;
      }      
      
      temp = temp.getNext();
    }
    
    return false;
  }
  
  public int size(){
    return this.count;
  }
  
  private Node getTail(){
    
    Node tail;
    
    tail = head;
    
    while(tail != null && tail.getNext() != null){
      tail = tail.getNext();
    }
    
    return tail;
  }
}



class Main {
  public static void main(String[] args) {
    
      MyList list = new MyList();
      list.add(new String("Joe"));
      list.add(new String("John"));
      list.add(new String("Mary"));
      list.add(new String("Jesse"));
      list.add(new String("Mike"));
      
      
      
      list.display();
      
      System.out.println("\nGet Joe " + list.get(0));
      System.out.println("\nGet Mike " + list.get(4));
      System.out.println("\nGet Unkn " + list.get(5));
   
      System.out.println("\nContains Joe " + 
               list.contains("Joe"));
      System.out.println("\nContains Mike " + 
              list.contains("Mike"));
      System.out.println("\nContains Danny " + 
              list.contains("Danny"));
            
      System.out.println("List Contents:");
      for(int i=0;i<list.size();i++){
        System.out.println(" List.get(" + i +") " + 
                  list.get(i));
      }
      
      list.remove(4);
      System.out.println("After removing Mike");
      for(int i=0;i<list.size();i++){
        System.out.println(" List.get(" + i +") " + 
                  list.get(i));
      }
      
      list.remove(0);
      System.out.println("After removing Joe");
      for(int i=0;i<list.size();i++){
        System.out.println(" List.get(" + i +") " + 
                  list.get(i));
      }
      
      list.remove(1);
      System.out.println("After removing Mary");
      for(int i=0;i<list.size();i++){
        System.out.println(" List.get(" + i +") " + 
                  list.get(i));
      }
      
      list.remove(2);
      System.out.println("After removing out of bounds");
      for(int i=0;i<list.size();i++){
        System.out.println(" List.get(" + i +") " + 
                  list.get(i));
      }
      
      list.remove(0);
      list.remove(0);
      System.out.println("After removing all");
      for(int i=0;i<list.size();i++){
        System.out.println(" List.get(" + i +") " + 
                  list.get(i));
      }
      
    
  }
}