public class TestBox{
    public static void main(String args[]){
        Box hisbox=new Box();
        hisbox.setBox(10,20,30);
        System.out.println("hisbox的"+hisbox.printString());
        Box herbox=hisbox;
        System.out.println("herbox的"+herbox.printString());
        hisbox.width=100;
        System.out.println("修改了hisbox后herbox的"+herbox.printString());
    }
}