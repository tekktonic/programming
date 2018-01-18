    import java.io.File;
    import java.io.FileNotFoundException;
    import java.util.Scanner;
    import java.util.ArrayList;
    import java.util.Random;
    /**
     * This program randomly assigns people for a tag team tournament setup. The purpose of this is to make it quick and easy and hassle free.
     *
     * @author http://www.furaffinity.net/user/shadowolfox
     * @version 9/12/2014
     */
    public class RandomAssigner
    {
        public static void main(String[] args){
            ArrayList<fighter> Roster = new ArrayList<fighter>();
            ArrayList<String> NameList = new ArrayList<String>();
            ArrayList<Integer> PvList = new ArrayList<Integer>();
            ArrayList<String> Team = new ArrayList<String>();
            String filename = "FighterList.txt"; // Name of the Roster
            Scanner keyboard;                   // a scanner connected to keyboard
            Scanner inputFile = null;           // a scanner connected to the file containing slides
            File fighterFile = null;   // The fighter input file
            boolean earlyFinish = false;
            int earlyFinCount = 0;
     
            keyboard = new Scanner(System.in);
            System.out.println("Attempting to locate FighterList.txt");
            try{
                fighterFile = new File(filename);     // create a File associated with filename
                inputFile = new Scanner(fighterFile); // connect a Scanner to the File              
                System.out.println("File successfully located.\n");
            }
            catch (FileNotFoundException e)
            {
                System.out.print("File Not Found: " + filename);
            }
     
            String firstname = "";
            String lastname = "";
            boolean error1 = false;
            boolean error2 = false;
     
            while(inputFile.hasNext()){
                try{
                    firstname = inputFile.next();
                    if(!inputFile.hasNextInt())
                        lastname = inputFile.next();
                    NameList.add(firstname + " " + lastname);
                    PvList.add(inputFile.nextInt());
                    firstname = "";
                    lastname = "";
                }
                catch (java.util.InputMismatchException e){
                    System.out.println("When reading the file, an error occured. Make sure the text file is in the following format.");
                    System.out.println("FirstName LastName pvScore");
                    error1 = true;
                    break;
                }
            }
     
            if(error1 == false){
                if(NameList.size() == PvList.size()){
                    for(int i = 0; i < NameList.size(); i++){
                        fighter holder = new fighter(NameList.get(i), PvList.get(i));
                        Roster.add(holder);
                    }
     
                }
                else{
                    System.out.println("Something went wrong. There are not as many names as there are perceived value scores. Make sure the text file is in the following format.");
                    System.out.println("FirstName LastName pvScore");
                }
     
                Random RNG = new Random();
                int pairings = NameList.size() / 2;
                int totalFighters = NameList.size();
                fighter newFighter;
                fighter partner;
                int randomInt;
                int count = 0;
     
                if(totalFighters % 2 != 0)
                    System.out.println("Unable to randomize participants. There is an odd number of members.");
                else{
                    while(earlyFinish == false){
                        for(int i = 0; i < pairings; i++){
                            randomInt = RNG.nextInt(totalFighters); // initiating random number generator
                            newFighter = Roster.get(randomInt); // Initiating first fighter
                            while(newFighter.isUsed()){ // Checking to see if the fighter has been used. Keeps searching until there's one that isn't used
                                randomInt = RNG.nextInt(totalFighters);
                                newFighter = Roster.get(randomInt);
                            }
                            newFighter.setUsed();
                            randomInt = RNG.nextInt(totalFighters); // Initiating RNG for partner
                            partner = Roster.get(randomInt); // Initiating partner
                            while((partner.isUsed() == true) || (newFighter.equals(partner)) || (newFighter.pv + partner.pv > 7)){ // Checking to see if the fighter has been used. Keeps searching until there's one that isn't used. Also
                                randomInt = RNG.nextInt(totalFighters);                                               // makes sure that the PV values do not exceed seven
                                partner = Roster.get(randomInt);
                                count++;
                                if(count > 1000000){
                                    error2 = true;
                                    break;
                                }
                            }              
                            if(error2 == true)
                                break;
                            partner.setUsed();
                            Team.add(newFighter.name + " (" + newFighter.pv + ") is paired with " + partner.name + " (" + partner.pv + ")");
                        }
     
                        if(error2 == true){ // Reruns the program if there was an error
                            System.out.println("Unable to properly randomly assign partners. Running again to attempt to obtain proper random assignments. " + ( 1 + earlyFinCount));
                            error2 = false;
                            count = 0;
                            earlyFinCount++;
                            Roster.clear();
                            for(int i = 0; i < NameList.size(); i++){
                                fighter holder = new fighter(NameList.get(i), PvList.get(i));
                                Roster.add(holder);
                                Team.clear(); // Clearing out the data of any previous matches made
                            }
                        }
                        else
                            earlyFinish = true;
     
                        if(earlyFinCount >= 100)
                            earlyFinish = true;
                    }
                }
                System.out.println("");
                for(int i = 0; i < Team.size(); i++){
                    System.out.println(Team.get(i));
                }
     
            }
           
            if(earlyFinCount >= 100)
                System.out.println("It may be possible that there is no combination that would make the PVs work.");
               
            System.out.println("\nPress enter to close the window.");
            String dummy = keyboard.nextLine();
        }        
        static class fighter{
            private String name; // Holds the figher's name
            private int pv; // Hold's the Perceived Value
            private boolean used; // Allows to see if the fighter has already been paired
     
            public fighter(){ // Basic constructor for the fighter. Not necessary, just here due to habit.
                name = "";
                pv = 1;
                used = false;
            }
     
            public fighter(String Name, int PV){ // Allows for the construction of new fighters with objects passed to it
                name = Name;
                pv = PV;
                used = false;
            }
     
            public void setUsed(){ // Allows for the use of fighter.setUsed(); to change a fighter's status to used.
                used = true;
            }
     
            public void reset(){ //Allows for the use of fighter.reset() in order to rerun the program
                used = false;
            }
     
            public boolean isUsed(){ // Allows for the use of fighter.isUsed(); to check if a fighter has been paired already
                return used;
            }
     
            @Override
            public String toString(){
                return (name + " " + pv + " " + used);
            }
        }
    }

