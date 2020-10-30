import controlP5.*; 
import processing.serial.*;

Serial port;

ControlP5 cp5; 
PFont font, fontslide, fontTitle;


int dot = 0;
int dir;
int angle;
int speed;
int[] degree = {1, 2, 3}; //For passing over to arduino
int graphRot = 0;

String rotStg;

void setup() { 
  size(950, 300);    

  printArray(Serial.list());  

  port = new Serial(this, "COM3", 9600);  //Comment if no arduino is connected

  cp5 = new ControlP5(this);
  font = createFont("Arial", 20);  
  fontslide = createFont("Arial", 12);  
  fontTitle = createFont("Arial", 18);  

//Add GUI elements

  //Art 1
  cp5.addButton("right")      
    .setPosition(100, 70) 
    .setSize(120, 70)      
    .setFont(font)
    .setLabel("CCW")
    ;   
  cp5.addButton("left")     
    .setPosition(100, 150)  
    .setSize(120, 70)      
    .setFont(font)
    .setLabel("CW")
    ;

  //Art2
  cp5.addButton("right2")      
    .setPosition(240, 70) 
    .setSize(120, 70)      
    .setFont(font)
    .setLabel("RIGHT")
    ;   
  cp5.addButton("left2")     
    .setPosition(240, 150)  
    .setSize(120, 70)      
    .setFont(font)
    .setLabel("LEFT")
    ;

  //Art3
  cp5.addButton("right3")      
    .setPosition(380, 70) 
    .setSize(120, 70)      
    .setFont(font)
    .setLabel("RIGHT")
    ;   
  cp5.addButton("left3")     
    .setPosition(380, 150)  
    .setSize(120, 70)      
    .setFont(font)
    .setLabel("LEFT")
    ;

  //Art4
  cp5.addButton("right4")      
    .setPosition(520, 70) 
    .setSize(120, 70)      
    .setFont(font)
    .setLabel("RIGHT")
    ;   
  cp5.addButton("left4")     
    .setPosition(520, 150)  
    .setSize(120, 70)      
    .setFont(font)
    .setLabel("LEFT")
    ;
    
    //Art5
  cp5.addButton("right5")      
    .setPosition(660, 70) 
    .setSize(120, 70)      
    .setFont(font)
    .setLabel("Right")
    ;   
  cp5.addButton("left5")     
    .setPosition(660, 150)  
    .setSize(120, 70)      
    .setFont(font)
    .setLabel("LEFT")
    ;
  
   //Art6
    cp5.addButton("right6")      
    .setPosition(800, 70) 
    .setSize(120, 70)      
    .setFont(font)
    .setLabel("CW")
    ;   
  cp5.addButton("left6")     
    .setPosition(800, 150)  
    .setSize(120, 70)      
    .setFont(font)
    .setLabel("CCW")
    ;
  
 //Gripper Control
  cp5.addButton("GripperOpen")     
    .setPosition(680, 240)  
    .setSize(80, 40)      
    .setFont(font)
    .setLabel("Open")
    ;
  cp5.addButton("GripperClose")     
    .setPosition(590, 240)  
    .setSize(80, 40)      
    .setFont(font)
    .setLabel("Close")
    ;

 //Demo
  cp5.addButton("demo")     
    .setPosition(420, 240)  
    .setSize(80, 40)      
    .setFont(createFont("Arial", 18))
    .setLabel("DEMO")
    ;

//Home
  cp5.addButton("calib")     
    .setPosition(5, 240)  
    .setSize(80, 40)      
    .setFont(createFont("Arial", 18))
    .setLabel("HOME")
    ;


//Sliders
  cp5.addSlider("duration")
    .setPosition(150, 240)
    .setRange(0, 255)
    .setValue(200)
    .setSize(130, 20)
    .setLabel("SPEED (rev/min)")
    .setFont(fontslide)
    .setScrollSensitivity(0.03)

    ;

  cp5.addSlider("rotation")
    .setPosition(150, 260)
    .setRange(0, 360)
    .setValue(0)
    .setSize(130, 20)
    .setLabel("ROTATION (degs)")
    .setFont(fontslide)
    .setScrollSensitivity(0.03)
    .setNumberOfTickMarks(3)
    .snapToTickMarks(false)
    ;
}

void draw() { 

  background(0, 0, 250); 
  fill(50, 250, 237);    

  //Titles
  textFont(font);
  text("THOR GUI", width/2.4, 30); 
  textFont(fontTitle);
  text("Art 1", 140, 60); 
  text("Art 2", 280, 60);
  text("Art 3", 420, 60);
  text("Art 4", 560, 60);
  text("Art 5/6", 700, 60);
  text("Rotate Gripper", 800, 60);
  text("Gripper:", 520, 260);


  //Graphic
  graphic();
}

void graphic()
{
  if (dot != graphRot && dir == 1)
  {
    dot++;
  } else if (dot != graphRot && dir == -1)
  {
    dot--;
  }

  pushMatrix();
  translate(50, 145);
  circle(0, 0, 80);
  fill(#ffffff);
  translate(0, 0);
  rotate(radians(dot));
  circle(0, 38, 8);
  popMatrix();
}

//Write letter for Arduino switch statements//
void right() {
  port.write('r');
  port.write(this.speed);  //Get speed
  port.write(rotStg);      //Get the degree of roation string
  graphRot = graphRot - angle; //Move dot
  dir = -1;
}

void left() {
  port.write('l');
  port.write(this.speed); 
  port.write(rotStg);
  graphRot=angle + graphRot; //Move dot
  dir = 1;
}

void right2() {
  port.write('k');
  port.write(this.speed);
  port.write(rotStg);
  graphRot=angle + graphRot;
  dir = 1;
}

void left2() {
 port.write('j');
  port.write(this.speed);
  port.write(rotStg);
  graphRot=angle + graphRot;
  dir = 1;
}

void right3() {
  port.write('n');
  port.write(this.speed);
  port.write(rotStg);
}

void left3() {
  port.write('m');
  port.write(this.speed);
  port.write(rotStg);
}

void right4() {
  port.write('h');
  port.write(this.speed);
  port.write(rotStg);
}

void left4() {
  port.write('i');
  port.write(this.speed);
  port.write(rotStg);
}

void right5() {
  port.write('o');
  port.write(this.speed);
  port.write(rotStg);
}

void left5() {
  port.write('p');
  port.write(this.speed);
  port.write(rotStg);
}

void right6() {
  port.write('q');
  port.write(this.speed);
  port.write(rotStg);
}

void left6() {
  port.write('t');
  port.write(this.speed);
  port.write(rotStg);
}

void GripperOpen() {
  port.write('z');
  port.write('\0');
  port.write('\0');
}

void GripperClose() {
  port.write('x');
  port.write('\0');
  port.write('\0');
}

void s() {
}

void demo() {
  port.write('s');
  port.write('\0');
  port.write('\0');
}

void calib() {
  graphRot=0;
  dot = 0;
  port.write('c');
  port.write('\0');
  port.write('\0');
}


void duration(int duration)
{
  speed = duration;
}

//This function takes the degree and splits it into a string of three chars since you can only pass along 255 bits (so any degree above 255 would not get sent properly
void rotation(int rotation)
{ 
  angle = rotation;
  for (int i = 2; i >= 0; i--)
  {
    //generate string
    int temp = rotation%(10);
    degree[i] = temp;
    rotation/=10;
  }
  //Send start and end packets
  rotStg = "<" + degree[0]  +
    " " + degree[1] +
    " " + degree [2] +
    ">";
}
