import processing.serial.*;

Serial myPort;
String val;

// Declare some global variables
XML response;
String forecast;

void setup() {
  String portName = Serial.list()[3];
  myPort = new Serial(this, portName, 9600);
  // Load the XML file
  response = loadXML("response.xml");
  
  // Parse down to what you want
  XML parsed = response.getChild("channel/item/yweather:condition");

  // Put the sunrise and sunset times in strings
  forecast = parsed.getString("code");
  
  // Print the results
  println(forecast);
}
