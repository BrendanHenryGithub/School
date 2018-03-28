package pkg2;
import java.util.*;
import pkg2.People;
public class PeopleTest{
    public static void main(String args[]){
        People p =new People("李华","4435");
        System.out.println("名字是:"+p.getName());
        System.out.println("ID是:"+p.getID());
        p.setName("小明");
        p.setID("9999");
        System.out.println("名字是:"+p.getName());
        System.out.println("ID是:"+p.getID());
        p.setName("小明sdkfjsdf");
        p.setID("9999sss");
        System.out.println("名字是:"+p.getName());
        System.out.println("ID是:"+p.getID());
        p.testprint();
    }
    static int var1;
}