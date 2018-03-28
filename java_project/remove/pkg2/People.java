package pkg2;
import pkg2.PeopleTest;
class People {
    String name;
    String ID;

    People (String n, String id){
        name=n;
        ID=id;
    }

    String getName(){
        return name;
    }

    String getID(){
        return ID;
    }

    boolean setName(String n){
        boolean flag=false;
        if(n.length()<=4){
            name=n;
            flag=true;
        }
        else{
            System.out.println("不是合法的名字!");
        }
        return flag;
    }

    boolean setID(String id){
        boolean flag=false;
        if (id.length()<=4){
            ID=id;
            flag=true;
        }
        else{
            System.out.println("不是合法的id!!!");
        }
        return flag;
    }

    void testprint(){
        System.out.println("test for var:"+PeopleTest.var1);
    }
}