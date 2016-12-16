import java.net.*;
import java.io.*;
import edu.wpi.first.wpilibj.networktables.NetworkTable;

class NTable
{
    public static void main(String [] args) throws Exception
    {
        String serverName = "localhost";
        int port = 3341; 
        try
        {
          Socket client = new Socket(serverName, port);
          OutputStream outToServer = client.getOutputStream();
          DataOutputStream out = new DataOutputStream(outToServer);

          InputStream inFromServer = client.getInputStream();
          DataInputStream in = new DataInputStream(inFromServer);
          NetworkTable.setClientMode();
          NetworkTable.setIPAddress("10.33.41.2");
          NetworkTable table = NetworkTable.getTable("cv");
          //Main loop
          while(true)
          {
              //send the value request
              out.write('\n');
              //grab the values
              Thread.sleep(100); // Update values every 100 ms
              String targetDataRaw = null;
              targetDataRaw = in.readLine();
              if(targetDataRaw == null)
                  break;
              if(targetDataRaw.isEmpty())
                  continue;
              // Implements the FRC 2015 Network Tables Protocol
              boolean found;
              double distance = 0, azimuth = 0, altitude = 0;
              String[] parsed = targetDataRaw.split(";");
              for(String s: parsed)
              {
                  String[] var = s.split(":");
                  table.putNumber(var[0], Double.parseDouble(var[1]);
              }
	  }
          out.close();
          in.close();
          client.close();
      }
      catch(IOException e)
      {
          e.printStackTrace();
      }
   }    
    
}
