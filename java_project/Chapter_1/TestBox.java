public class TestBox{
    public static void main(String args[]){
        Box hisbox=new Box();
        hisbox.setBox(10,20,30);
        System.out.println("hisbox��"+hisbox.printString());
        Box herbox=hisbox;
        System.out.println("herbox��"+herbox.printString());
        hisbox.width=100;
        System.out.println("�޸���hisbox��herbox��"+herbox.printString());
    }
}