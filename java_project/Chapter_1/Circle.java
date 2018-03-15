public class Circle{
    double radius;
    void setRadius(double r){
        radius=r;
    }
    double getArea(){
        return Math.PI*radius*radius;
    }
    double getperimeter(){
        return 2*radius*Math.PI;
    }
    String printString(){
        return "半径为："+radius+"; 周长为: "+getperimeter() +"; 面积为: "+getArea()+" 。";
    }
}