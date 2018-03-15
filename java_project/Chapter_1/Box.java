public class Box{
    int width;
    int height;
    int length;
    void setBox(int w,int h,int l){
        width=w;
        height=h;
        length=l;
    }
    String printString(){
        return "width="+width+"; height="+height+" ;length="+length+" ¡£";
    }
}