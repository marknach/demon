import java.util.Scanner;

Scanner s;
int numberOfVectors;

  /*public static void main(String args[]) 
  {
      PApplet.main("Demon", args);
  }*/



void setup()
{
    size(800, 600); 
    frameRate(30);
    background(0);
    
    s = new Scanner(System.in);
    if(s.hasNextLine())
    {
        numberOfVectors = Integer.parseInt(s.nextLine());
    }
    else
    {
       System.out.println("Fatal error. Will now exit.");
       System.exit(1); 
    }

    
}
 
 
 
 
 
 

void draw()
{
    background(0);
    noStroke();
    //translate(width/2,height/2,0);
    fill(255,255,255);
    for(int i = 0; i < numberOfVectors; i++)
    {
        while(!s.hasNextLine());
        
        String[] str = s.nextLine().split(",");
        
        float x = 200 * Float.parseFloat(str[0]);
        float y = 200 * Float.parseFloat(str[1]);
        float r = 200 * Float.parseFloat(str[2]);
        
        ellipse(x,y,r,r);

    }
    

}


