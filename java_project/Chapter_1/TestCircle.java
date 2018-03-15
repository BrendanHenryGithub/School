public class TestCircle{
    public static void main(String args[]){
        Circle cir1=new Circle();
        Circle cir2=new Circle();
        Circle cir3=new Circle();
        cir1.setRadius(10);
        cir2.setRadius(20);
        cir3.setRadius(30);
        System.out.println("circle1µÄ"+cir1.printString());
        System.out.println("circle2µÄ"+cir2.printString());
        System.out.println("circle3µÄ"+cir3.printString());
    }
}