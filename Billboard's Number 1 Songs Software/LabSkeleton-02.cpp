/*==========================================================================

  Skeleton02.cpp
  Skeleton code for Project #2 for Semester II, 2025.

	PURPOSE:
	   Program reads data from a Random Access file, and processing is done
	   with the Hierarchical and Set ADTs.

  Created by Dr. John Charlery on 04/07/2025.
  Copyright (c) 2025 University of the West Indies. All rights reserved.

==========================================================================*/

//============================VERY IMPORTANT================================
//		You can use this code as a start-up, BUT, you are required to
//			modify the documentation and code accordingly. You should have
//			your own class names, your own functions' names, etc. You are
//			also required to have documentation within your code.
//
//		DO NOT SIMPLY SUBMIT THE CODE WHICH HAS BEEN GIVEN HERE!
//==========================================================================


/************************************************************************************
  Step 1: Always include the header file wx.h
*************************************************************************************/
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#  include <wx/wx.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;


struct record
    {
        char month[10];
        int  year;
        char artist[50];
        char title[50];
        char label[15];
        int  numweeks;
    };
typedef struct record Record;




// Other miscellaneous functions' protypes
string makeRecord(string, int, string, string, string, int);
string makeRecord(Record);



// the ADTs header files
#include "BSTree.h"					// This is only PARTIAL! You must complete
#include "AVLTree.h"
#include "RBTree.h"
#include "SPLAYTree.h"
#include "MaxHeap.h"
#include "MinHeap.h"
#include "Set.h"


//Global pointers for the ADT containers
BSTree* bst = new BSTree();

// ... Add in other ADTs as global containers
AVLTree* avl=new AVLTree();
RBTree* rb=new RBTree();
SplayTree* splay=new SplayTree();
MaxBinaryHeap* maxheap=new MaxBinaryHeap();
MinBinaryHeap* minheap=new MinBinaryHeap();
SetADT* set=new SetADT();
SetADT* setA = new SetADT();
SetADT* setB = new SetADT();
SetADT* setIntersection = new SetADT();

/************************************************************************************
*************************************************************************************
  Step 2: Name an inherited application class from wxApp and declare it with
	  the function to execute the program
*************************************************************************************
*************************************************************************************/
class ProjectApp: public wxApp
  {
	 virtual bool OnInit();
  };





/************************************************************************************
*************************************************************************************
   Step 3: Declare the inherited main frame class from wxFrame. In this class
	   also will ALL the events handlers be declared
*************************************************************************************
*************************************************************************************/
class ProjectFrame: public wxFrame
  {
	 private:
		DECLARE_EVENT_TABLE() //To declare events items

	 public:
		ProjectFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

		//Functions for File Menu Items
		void OnOpenFile(wxCommandEvent& event);
		void OnCreateADTs(wxCommandEvent& event);
		void OnDisplay(wxCommandEvent& event);
		void OnClearWindow(wxCommandEvent& event);
		void OnExit(wxCommandEvent& event); 	//handle for Quit function



		//Function for Help Menu Item
		void OnAbout(wxCommandEvent& event);
		void OnHelp(wxCommandEvent& event);


		//Functions for the Partial BST Menu Items
		void OnInorderBST(wxCommandEvent& event);
		void OnPreorderBST(wxCommandEvent& event);
		void OnPostorderBST(wxCommandEvent& event);
		void OnDeleteBST(wxCommandEvent& event);
        //Etc... etc...


		//Functions for AVL Menu Items
		void OnAVL_Inorder(wxCommandEvent& event);
		void OnAVL_Preorder(wxCommandEvent& event);
		void OnAVL_Postorder(wxCommandEvent& event);
		void OnAVL_Delete(wxCommandEvent& event);

		//Functions for RBT Menu Items
		void OnRB_Inorder(wxCommandEvent& event);
		void OnRB_Preorder(wxCommandEvent& event);
		void OnRB_Postorder(wxCommandEvent& event);
		void OnRB_Delete(wxCommandEvent& event);

		//Functions for Splay Menu Items
		void OnSPLAY_Inorder(wxCommandEvent& event);
		void OnSPLAY_Preorder(wxCommandEvent& event);
		void OnSPLAY_Postorder(wxCommandEvent& event);
		void OnSPLAY_Delete(wxCommandEvent& event);

		//Functions for MaxHeap Menu Items
		void OnMaxHeap_Display(wxCommandEvent& event);
		void OnMaxHeap_Delete(wxCommandEvent& event);
		void OnMaxHeap_Sort(wxCommandEvent& event);

		//Functions for MinHeap Menu Items
		void OnMinHeap_Display(wxCommandEvent& event);
		void OnMinHeap_Delete(wxCommandEvent& event);
		void OnMinHeap_Sort(wxCommandEvent& event);

		//Functions for Set Menu items
		void OnSetA_Display(wxCommandEvent& event);
		void OnSetB_Display(wxCommandEvent& event);
		void OnSetIntersection_Display(wxCommandEvent& event);
		void OnSetA_Delete(wxCommandEvent& event);
		void OnSetB_Delete(wxCommandEvent& event);

		//Public attributes for the Client Area features
		wxTextCtrl* MainEditBox;
		wxTextCtrl* filenameTextBox;
		wxTextCtrl* txtTitle;
		wxString CurrentDocPath;	// To store the Path to the file which has been opened

  };



/************************************************************************************
*************************************************************************************
  Step 4. Declare the compiler directives
*************************************************************************************
*************************************************************************************/
DECLARE_APP(ProjectApp)		// Declare Application class
IMPLEMENT_APP(ProjectApp)		// Create Application class object


enum
    {
      	// File menu items
		ID_OpenFile	= wxID_HIGHEST + 1,		//File menu item
		ID_CreateADTs,
		ID_Display,
		ID_ClearWindow,
		ID_Exit,



		// BST menu items
		ID_InorderBST,
		ID_PreorderBST,
		ID_PostorderBST,
	    ID_DeleteBST,

		// AVL sub-menu items
		ID_AVL_Inorder,
		ID_AVL_Preorder,
		ID_AVL_Postorder,
		ID_AVL_Delete,

		// RBT sub-menu items
		ID_RB_Inorder,
		ID_RB_Preorder,
		ID_RB_Postorder,
		ID_RB_Delete,

		// Splay sub-menu items
		ID_SPLAY_Inorder,
		ID_SPLAY_Preorder,
		ID_SPLAY_Postorder,
		ID_SPLAY_Delete,

		// MaxHeap sub-menu items
		ID_MaxHeap_Display,
		ID_MaxHeap_Delete,
		ID_MaxHeap_Sort,

		// MinHeap sub-menu items
		ID_MinHeap_Display,
		ID_MinHeap_Delete,
		ID_MinHeap_Sort,

		// Stack sub-menu items
		ID_SetA_Display = 2001,
		ID_SetB_Display,
		ID_SetIntersection_Display,
		ID_SetA_Delete,
		ID_SetB_Delete
    };



BEGIN_EVENT_TABLE ( ProjectFrame, wxFrame )
      // Events for the "File" menu items
      EVT_MENU ( ID_OpenFile, 	 ProjectFrame::OnOpenFile )		//File Menu
      EVT_MENU ( ID_CreateADTs,  ProjectFrame::OnCreateADTs )
      EVT_MENU ( ID_Display,  	 ProjectFrame::OnDisplay )
      EVT_MENU ( ID_ClearWindow, ProjectFrame::OnClearWindow )
      EVT_MENU ( ID_Exit, 	  	 ProjectFrame::OnExit )


      // Events for the "BST" menu items
      EVT_MENU ( ID_InorderBST,  	ProjectFrame::OnInorderBST )
	  EVT_MENU ( ID_PreorderBST,    ProjectFrame::OnPreorderBST )
	  EVT_MENU ( ID_PostorderBST,    ProjectFrame::OnPostorderBST )
	  EVT_MENU ( ID_DeleteBST,    ProjectFrame::OnDeleteBST )

      // Events for the AVL sub-menu items
	  EVT_MENU ( ID_AVL_Inorder,  	ProjectFrame::OnAVL_Inorder )
	  EVT_MENU ( ID_AVL_Preorder,    ProjectFrame::OnAVL_Preorder )
	  EVT_MENU ( ID_AVL_Postorder,    ProjectFrame::OnAVL_Postorder )
	  EVT_MENU ( ID_AVL_Delete,    ProjectFrame::OnAVL_Delete )

      // Events for the RBT sub-menu items
	  EVT_MENU ( ID_RB_Inorder,  	ProjectFrame::OnRB_Inorder )
	  EVT_MENU ( ID_RB_Preorder,    ProjectFrame::OnRB_Preorder )
	  EVT_MENU ( ID_RB_Postorder,    ProjectFrame::OnRB_Postorder )
	  EVT_MENU ( ID_RB_Delete,    ProjectFrame::OnRB_Delete )

      // Events for the Splay submenu items
	  EVT_MENU ( ID_SPLAY_Inorder,  	ProjectFrame::OnSPLAY_Inorder )
	  EVT_MENU ( ID_SPLAY_Preorder,    ProjectFrame::OnSPLAY_Preorder )
	  EVT_MENU ( ID_SPLAY_Postorder,    ProjectFrame::OnSPLAY_Postorder )
	  EVT_MENU ( ID_SPLAY_Delete,    ProjectFrame::OnSPLAY_Delete )

	  // Events for the MaxHeap submenu items
	  EVT_MENU ( ID_MaxHeap_Display,    ProjectFrame::OnMaxHeap_Display )
	  EVT_MENU ( ID_MaxHeap_Delete,    ProjectFrame::OnMaxHeap_Delete )
	  EVT_MENU ( ID_MaxHeap_Sort,    ProjectFrame::OnMaxHeap_Sort )

	  // Events for the Minheap submenu items
	  EVT_MENU ( ID_MinHeap_Display,    ProjectFrame::OnMinHeap_Display )
	  EVT_MENU ( ID_MinHeap_Delete,    ProjectFrame::OnMinHeap_Delete )
	  EVT_MENU ( ID_MinHeap_Sort,    ProjectFrame::OnMinHeap_Sort )

	  // Events for the Set submenu items
	  EVT_MENU(ID_SetA_Display, ProjectFrame::OnSetA_Display)
	  EVT_MENU(ID_SetB_Display, ProjectFrame::OnSetB_Display)
	  EVT_MENU(ID_SetIntersection_Display, ProjectFrame::OnSetIntersection_Display)
	  EVT_MENU(ID_SetA_Delete, ProjectFrame::OnSetA_Delete)
	  EVT_MENU(ID_SetB_Delete, ProjectFrame::OnSetB_Delete)


END_EVENT_TABLE ()





/************************************************************************************
*************************************************************************************
  Step 5.  Define the Application class function to initialize the application
*************************************************************************************
*************************************************************************************/
bool ProjectApp::OnInit()
  {
      // Create the main application window
      ProjectFrame *frame = new ProjectFrame( wxT("COMP2611 - Data Structures"),
				    wxPoint(50,50),
				    wxSize(840,600) );

      // Display the window
      frame->Show(TRUE);

      SetTopWindow(frame);

      return TRUE;

  }




/************************************************************************************
*************************************************************************************
  Step 6:   Define the Constructor functions for the Frame class
*************************************************************************************
*************************************************************************************/
ProjectFrame::ProjectFrame ( const wxString& title, const wxPoint& pos, const wxSize& size)
		    : wxFrame((wxFrame *)NULL, -1, title, pos, size)
  {
	// Set the frame icon - optional
//	SetIcon(wxIcon(wxT("UWIIcon.xpm")));

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);


	// Create the main-menu items
	wxMenu *menuFile  	   =   new wxMenu;			// File main menu item
	wxMenu *menuBST  	   =   new wxMenu;			// Queue main menu item
	wxMenu *menuAVL = new wxMenu; // AVL main menu item
	wxMenu *menuRB =  new wxMenu; // Red-Black Tree main menu item
	wxMenu *menuSPLAY = new wxMenu; // Splay Tree main menu item
	wxMenu *menuMaxHeap = new wxMenu; // MaxHeap main menu item
	wxMenu *menuMinHeap = new wxMenu; // Minheap main menu item
	wxMenu *menuSet = new wxMenu; // Set main menu item
	wxMenu *menuHelp = new wxMenu; // Help main menu item


	//Create a Main menu bar
	wxMenuBar *menuBar = new wxMenuBar;



	//Append the main menu items to the Menu Bar
	menuBar->Append( menuFile, 		wxT("File") );
	menuBar->Append( menuBST, 		wxT("BST") );
	menuBar->Append(menuAVL,        wxT("AVL Tree"));
	menuBar->Append(menuRB,         wxT("Red-Black Tree"));
	menuBar->Append(menuSPLAY,      wxT("Splay Tree"));
	menuBar->Append(menuMaxHeap,    wxT("MaxHeap"));
	menuBar->Append(menuMinHeap,    wxT("MinHeap"));
	//menuBar->Append(menuSet,        wxT("Set"));
	menuBar->Append(menuHelp,       wxT("Help"));

	SetMenuBar(menuBar);

	//Append the sub-menu items to the File Main Menu item
	menuFile->Append( ID_OpenFile, 		wxT("Open File..."), 	wxT("Open an Existing file") );
	menuFile->Append( ID_CreateADTs,	wxT("Create ADTs"),		wxT("Populate ADTs from opened file") );
	menuFile->Append( ID_Display,  		wxT("Display File..."),	wxT("Display contents of opened file") );
	menuFile->Append( ID_ClearWindow,  	wxT("Clear Window"),	wxT("Clear display window") );
	menuFile->Append( ID_Exit, 	   		wxT("Exit"), 			wxT("Close and EXIT Program") );



	//Append the sub-menu items to the BST Main Menu item
	menuBST->Append( ID_InorderBST,   wxT("Inorder"), 	wxT("Inorder traversal on BST"));
	menuBST->Append( ID_PreorderBST,  wxT("Preorder"),  wxT("Traverse BST in Preorder"));
	menuBST->Append( ID_PostorderBST,  wxT("Postorder"),  wxT("Traverse BST in Postorder"));
	menuBST->Append( ID_DeleteBST,  wxT("Delete Record"),  wxT("Delete a record from BST"));

	//Append the other sub-menu items to the the other Main Menu item

	//Append the sub-menu items to the AVL Tree Main Menu item
	menuAVL->Append( ID_AVL_Inorder, wxT("Inorder"), wxT("AVL Inorder Traversal"));
    menuAVL->Append( ID_AVL_Preorder, wxT("Preorder"), wxT("AVL Preorder Traversal"));
    menuAVL->Append( ID_AVL_Postorder, wxT("Postorder"), wxT("AVL Postorder Traversal"));
    menuAVL->Append( ID_AVL_Delete, wxT("Delete Record"), wxT("Delete from AVL Tree"));

	//Append the sub-menu items to the Red-Black Tree Main Menu item
	menuRB->Append( ID_RB_Inorder, wxT("Inorder"), wxT("RB Inorder Traversal"));
    menuRB->Append( ID_RB_Preorder, wxT("Preorder"), wxT("RB Preorder Traversal"));
    menuRB->Append( ID_RB_Postorder, wxT("Postorder"), wxT("RB Postorder Traversal"));
    menuRB->Append( ID_RB_Delete, wxT("Delete Record"), wxT("Delete from RB Tree"));

	//Append the sub-menu items to the SPLAY Tree Main Menu item
	menuSPLAY->Append( ID_SPLAY_Inorder, wxT("Inorder"), wxT("SPLAY Inorder Traversal"));
    menuSPLAY->Append( ID_SPLAY_Preorder, wxT("Preorder"), wxT("SPLAY Preorder Traversal"));
    menuSPLAY->Append( ID_SPLAY_Postorder, wxT("Postorder"), wxT("SPLAY Postorder Traversal"));
    menuSPLAY->Append( ID_SPLAY_Delete, wxT("Delete Record"), wxT("Delete from SPLAY Tree"));

	//Append the sub-menu items to the MaxHeap Tree Main Menu item
	menuMaxHeap->Append( ID_MaxHeap_Display, wxT("Display"), wxT("MaxHeap Display All"));
    menuMaxHeap->Append( ID_MaxHeap_Delete, wxT("Delete Record"), wxT("MaxHeap Delete from Tree"));
    menuMaxHeap->Append( ID_MaxHeap_Sort, wxT("Sort Record"), wxT("MaxHeap Sort"));

	//Append the sub-menu items to the MinHeap Tree Main Menu item
    menuMinHeap->Append( ID_MinHeap_Display, wxT("Display"), wxT("MinHeap Display All"));
    menuMinHeap->Append( ID_MinHeap_Delete, wxT("Delete Record"), wxT("MinHeap Delete from Tree"));
    menuMinHeap->Append( ID_MinHeap_Sort, wxT("Sort Record"), wxT("MinHeap Sort"));

	//Append the sub-menu items to the Set Tree Main Menu item
	wxMenu* setMenu = new wxMenu;
	setMenu->Append(ID_SetA_Display, wxT("Display Set A"));
	setMenu->Append(ID_SetB_Display, wxT("Display Set B"));
	setMenu->Append(ID_SetIntersection_Display, wxT("Display Intersection"));
	setMenu->AppendSeparator();
	setMenu->Append(ID_SetA_Delete, wxT("Delete from Set A"));
	setMenu->Append(ID_SetB_Delete, wxT("Delete from Set B"));

	// Create and populate Help menu
	menuHelp->Append(wxID_ABOUT, wxT("&About\tF1"), wxT("Show info about the app"));
	menuHelp->Append(wxID_HELP, wxT("&Help\tF2"), wxT("How to use this program"));

	// Bind menu events to handlers
	Bind(wxEVT_MENU, &ProjectFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &ProjectFrame::OnHelp, this, wxID_HELP);

	menuBar->Append(setMenu, wxT("&Set"));

	// ... and now... attach this main menu bar to the frame
	SetMenuBar( menuBar );

	// Create a status bar just for fun
	CreateStatusBar(3);

	//Put something in the first section of the status bar
	SetStatusText( wxT("Ready..."), 0 );

	//Put something in the Second section of the status bar
	SetStatusText( wxT("Assignment: Jayden Cummmins"), 1 );

	//Put something in the Third section of the status bar
	SetStatusText( wxT("400013734"), 2 );




	//Set up the panel for data display
//=========================================================================================
//=========================== DO NOT CHANGE THE CODE IN THIS SECTION ======================
//=========================================================================================

	wxPanel 	*panel = new wxPanel(this, -1);
	wxBoxSizer 	*vbox  = new wxBoxSizer(wxVERTICAL);		//Vertical sizer for main window
	wxBoxSizer 	*hbox1 = new wxBoxSizer(wxHORIZONTAL);		//Horizontal sizer for main window

	//Add two textboxes to the panel for data display
	wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);		//Horizontal sizer for filename window
	wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);		//Horizontal sizer for display window

	wxStaticText *fileLabel    = new wxStaticText(panel, wxID_ANY, wxT("File Name"));
	wxStaticText *displayLabel = new wxStaticText(panel, wxID_ANY, wxT("Display"));

	//Initialize the filename textbox window
	filenameTextBox = new wxTextCtrl(panel, wxID_ANY, wxT("No File Opened Yet..."));

	//Initialize the display window
	MainEditBox = new wxTextCtrl(panel, wxID_ANY, wxT("No Data Available Yet..."),
				      wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE | wxTE_RICH);


	//Position the labels and textboxes in the panel
	hbox1->Add(fileLabel, 0, wxRIGHT, 8);
	hbox1->Add(filenameTextBox, 1);
	vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

	vbox->Add(-1, 10);
	hbox2->Add(displayLabel, 0);
	vbox->Add(hbox2, 0, wxLEFT | wxTOP, 10);
	vbox->Add(-1, 10);

	hbox3->Add(MainEditBox, 1, wxEXPAND);
	vbox->Add(hbox3, 1, wxLEFT | wxRIGHT | wxEXPAND, 10);

	vbox->Add(-1, 25);
	panel->SetSizer(vbox);

	Centre();

  }


//=====================================================================
//=========== Other Support Functions =================================
//=====================================================================




string makeRecord(Record rec)
    {
        string recordStr(rec.month);
        recordStr.append(" \t");

        recordStr.append(to_string(rec.year) + " \t");
        recordStr.append("\t\t");
        recordStr.append(rec.artist);
        recordStr.append("\t\t");
		recordStr.append(rec.title);
        recordStr.append("\t\t");
		recordStr.append(rec.label);
        recordStr.append("\t\t");
        recordStr.append(to_string(rec.numweeks));

        return recordStr;
    }




/************************************************************************************
*************************************************************************************
  Step 7:  Define member functions for the Frame class
*************************************************************************************
*************************************************************************************/


//===================================================================================
//=========== Definition for the File Functions =====================================
//===================================================================================

void ProjectFrame::OnOpenFile(wxCommandEvent& event )
    {
       	// Creates a "open file" dialog with 3 file types
    	wxFileDialog *OpenDialog = new wxFileDialog( this,
            (wxT("Choose a file to open")), wxEmptyString, wxEmptyString,
			(wxT("Data Files (*.dat)|*.dat|Text files (*.txt)|*.txt|All files (*.*)|*.*")),
			wxFD_OPEN, wxDefaultPosition);

        if (OpenDialog->ShowModal() == wxID_OK)    // if the user click "Open" instead of "cancel"
			{
            	// Sets our current document to the file the user selected
            	CurrentDocPath = OpenDialog->GetPath();

				//Clean up filename textbox and Display file name in filename textbox
				filenameTextBox->Clear();
				filenameTextBox->AppendText(CurrentDocPath);

				// Set the Title
				SetTitle(wxString("COMP2611 - Data Structures : 400013734"));


				//Opens the file and display the contents in the MainEditBox
 				ifstream infile(CurrentDocPath.mb_str(), ios::in|ios::binary);

  				// Check to see if a valid file was opened.
				if (!infile)
					{
						MainEditBox->AppendText("\n\n\n\n\t\t\t\tNo Data file opened as yet...\n\n");
						return;
					}

     			Record rec;				     // variable to read the data from the binary file
     			string strRecord = "";		 // Variable to store record as a string


                // Move the Read/Write head to the start of the file
        		infile.seekg(0);



                // Clear the MainEditBox
                MainEditBox->Clear();


         		while (!infile.eof())
            		{
						infile.read(reinterpret_cast<char* >(&rec), sizeof(Record));

						// Make sure rec is not an empty record before trying to display it
						if (rec.month != "")
							{
								strRecord = makeRecord(rec);

								// Convert record (a string) to wxRecord (a wxWidget string)
								MainEditBox->AppendText(strRecord);
								MainEditBox->AppendText("\n");

								//Reset the record variable
								strRecord = "";
                    		}

            		}  // End while
			}
    }







void ProjectFrame::OnDisplay(wxCommandEvent& event)
{
    Record rec;
    MainEditBox->Clear();

    ifstream infile(CurrentDocPath.mb_str(), ios::in | ios::binary);
    if (!infile) {
        MainEditBox->AppendText("ERROR: Could not open file.\n");
        cerr << "ERROR: Could not open file: " << CurrentDocPath.mb_str() << endl;
        return;
    }

    int count = 0;

    while (infile.read(reinterpret_cast<char*>(&rec), sizeof(Record))) {
        // Skip empty or malformed records
        if (strlen(rec.month) == 0 || rec.month[0] == '\0')
            continue;

        count++;

        string strRecord = string(rec.month) + " | " + to_string(rec.year) + " | " +
                           string(rec.artist) + " | " + string(rec.title) + " | " +
                           string(rec.label) + " | " + to_string(rec.numweeks);

        MainEditBox->AppendText(wxString(strRecord.c_str(), wxMBConvUTF8()) + "\n");
    }

    if (count == 0) {
        MainEditBox->AppendText("No records found in file.\n");
        cerr << "NOTE: File read but no records were processed.\n";
    }
}




void ProjectFrame::OnExit(wxCommandEvent& event)
    {
		wxMessageBox(wxT("Good-bye!"), wxT("Exit"), wxOK | wxICON_INFORMATION, this);
		Close(TRUE); // Close the window
    }







int getMonthNumber(const char* month) {
    string m(month);
    if (m == "January") return 1;
    if (m == "February") return 2;
    if (m == "March") return 3;
    if (m == "April") return 4;
    if (m == "May") return 5;
    if (m == "June") return 6;
    if (m == "July") return 7;
    if (m == "August") return 8;
    if (m == "September") return 9;
    if (m == "October") return 10;
    if (m == "November") return 11;
    if (m == "December") return 12;
    return 0; // unknown month
}


void ProjectFrame::OnCreateADTs(wxCommandEvent& event)
	{
		Record  rec;
		string strRecord;

		// Clear the MainEditBox
		MainEditBox->Clear();

		//open the file
		ifstream infile(CurrentDocPath.mb_str(), ios::in|ios::binary);

		// Check to see if a valid file was opened.
		if (!infile)
			{
				MainEditBox->AppendText("\n\n\t\t\t\tNo Data file opened as yet...\n\n");
				return;
			}

		MainEditBox->AppendText("Reading and inserting...\n");

        // Move the Read/Write head to the start of the file
		infile.seekg(0);


        while (infile.read(reinterpret_cast<char*>(&rec), sizeof(Record))) {

		MainEditBox->AppendText("Read one record...\n");
        // Prevent crashing on partial read
        if (infile.gcount() != sizeof(Record)) break;

        // Skip empty or malformed records
        if (strlen(rec.month) == 0 || rec.month[0] == '\0'){
			MainEditBox->AppendText("Skipped empty record.\n");
			continue;
		}

        // 1. BST takes all the records
        MainEditBox->AppendText("Inserting into BST...\n");
        bst->insert(rec.month, rec.year, rec.artist, rec.title, rec.label, rec.numweeks);

		MainEditBox->AppendText("Checking label: ");
		MainEditBox->AppendText(wxString(rec.label, wxConvUTF8));
		MainEditBox->AppendText("\n");

        // 2. AVL Tree: Arista
        if (strncmp(rec.label, "Arista", 6) == 0) {
			 cout << "Inserting into AVL...\n" << endl;
            avl->insert(rec.month, rec.year, rec.artist, rec.title, rec.label, rec.numweeks);
        }

        // 3. RB Tree: Columbia
        if (strncmp(rec.label, "Columbia", 8) == 0) {
			cout << "Inserting into RB...\n" << endl;
            rb->insert(rec.month, rec.year, rec.artist, rec.title, rec.label, rec.numweeks);
        }

        // 4. Splay Tree: EMI
        if (strncmp(rec.label, "EMI", 3) == 0) {
			cout << "Inserting into Splay...\n" << endl;
            splay->insert(rec.month, rec.year, rec.artist, rec.title, rec.label, rec.numweeks);
			cout << "Splay insert completed." << endl;
        }

        // 5. MaxHeap and MinHeap: Songs of 1990
        if (rec.year == 1990) {
			cout << "Inserting into heaps...\n" << endl;
            int monthNum = getMonthNumber(rec.month);
            maxheap->insert(rec.month, rec.year, rec.artist, rec.title, rec.label, monthNum);
            minheap->insert(rec.month, rec.year, rec.artist, rec.title, rec.label, monthNum);
        }

        // 6. Set A: before 1995
        if (rec.year < 1995) {
			cout << "Inserting into Set A...\n" << endl;
            setA->insert(rec.month, rec.year, rec.artist, rec.title, rec.label, rec.numweeks);
        }

        // 7. Set B: after 1994
        if (rec.year > 1994) {
			cout << "Inserting into Set B...\n" << endl;
            setB->insert(rec.month, rec.year, rec.artist, rec.title, rec.label, rec.numweeks);
        }

        // Display record (optional)
        strRecord = makeRecord(rec);
        MainEditBox->AppendText(wxString(strRecord.c_str(), wxMBConvUTF8()) + "\n");
        strRecord = "";
    }

    // 8. Intersection: matching artist in Set A and Set B
    try {
        for (const auto& recA : setA->getSet()) {
            for (const auto& recB : setB->getSet()) {
                if (!recA.artist.empty() && !recB.artist.empty() &&
                    recA.artist == recB.artist) {
                    setIntersection->insert(recB.month, recB.year, recB.artist,
                                            recB.title, recB.label, recB.weeks);
                }
            }
        }
	} catch (...) {
		MainEditBox->AppendText("Error: Failed to compute intersection.\n");
	}

	MainEditBox->AppendText("ADT creation complete.\n");
	}



void ProjectFrame::OnClearWindow(wxCommandEvent& event)
	{
 		//Clear the MainEditBox
		MainEditBox->Clear();
	}


//=======================================================================================
//====================   Definition for the BST Functions      ==========================
//=======================================================================================

void ProjectFrame::OnInorderBST(wxCommandEvent& event)
	{
		// Clear the MainEditBox
		MainEditBox->Clear();

		MainEditBox->AppendText("\t\tBST Inorder: Not implemented yet!\n");

		// Get the string from the inorder traversal
		string record = bst->inOrder();

		// Convert record (a string) to wxRecord (a wxWidget string)
		wxString wxRecord(record.c_str(), wxConvUTF8);

		// Display the string in the MainEditBox
		MainEditBox->AppendText(wxRecord);
	}

void ProjectFrame::OnPreorderBST(wxCommandEvent& event)
	{
		// Clear the MainEditBox
		MainEditBox->Clear();

		MainEditBox->AppendText("\t\tBST Preorder: Not implemented yet!\n");

		// Get the string from the preorder traversal
		string record = bst->preOrder();

		// Convert record (a string) to wxRecord (a wxWidget string)
		wxString wxRecord(record.c_str(), wxConvUTF8);

		// Display the string in the MainEditBox
		MainEditBox->AppendText(wxRecord);
	}

void ProjectFrame::OnPostorderBST(wxCommandEvent& event)
	{
		// Clear the MainEditBox
		MainEditBox->Clear();

		MainEditBox->AppendText("\t\tBST postorder: Not implemented yet!\n");

		// Get the string from the postorder traversal
		string record = bst->postOrder();

		// Convert record (a string) to wxRecord (a wxWidget string)
		wxString wxRecord(record.c_str(), wxConvUTF8);

		// Display the string in the MainEditBox
		MainEditBox->AppendText(wxRecord);
	}

void ProjectFrame::OnDeleteBST(wxCommandEvent& event)
	{
		 // Clear the MainEditBox
		MainEditBox->Clear();

		// Prompt for song title
		wxString wxTitle = wxGetTextFromUser("Enter the song title to delete:", "Delete from BST");
		if (wxTitle.IsEmpty()) {
			MainEditBox->AppendText("No song title entered.\n");
			return;
		}

		// Prompt for artist (even if not used, it's part of assignment spec)
		wxString wxArtist = wxGetTextFromUser("Enter the artist:", "Delete from BST");
		if (wxArtist.IsEmpty()) {
			MainEditBox->AppendText("No artist entered.\n");
			return;
		}

		// Convert to std::string
		string titleStr = string(wxTitle.mb_str());
		string artistStr = string(wxArtist.mb_str());

		// Optional: check if title exists in BST (prevents pointless traversal)
		if (bst->inOrder().find(titleStr) == string::npos) {
			MainEditBox->AppendText("That title was not found in the BST.\n");
			return;
		}

		// Try deletion
		try {
			bst->remove(titleStr);  // Assuming remove(string title)
			MainEditBox->AppendText("BST Delete: " + wxTitle + " by " + wxArtist + " removed if it existed.\n");
		} catch (...) {
			MainEditBox->AppendText("Error: Could not delete from BST.\n");
		}
	}

//=======================================================================================
//====================   Definition for the AVL Functions      ==========================
//=======================================================================================

void ProjectFrame::OnAVL_Inorder(wxCommandEvent& event)
	{
		// Clear the MainEditBox
		MainEditBox->Clear();

		MainEditBox->AppendText("\t\tAVL_Inorder: Not implemented yet!\n");

		// Get the string from the inorder traversal
		string record = avl->inOrder();

		// Convert record (a string) to wxRecord (a wxWidget string)
		wxString wxRecord(record.c_str(), wxConvUTF8);

		// Display the string in the MainEditBox
		MainEditBox->AppendText(wxRecord);
	}

void ProjectFrame::OnAVL_Preorder(wxCommandEvent& event)
	{
		// Clear the MainEditBox
		MainEditBox->Clear();

		MainEditBox->AppendText("\t\tAVL_Preorder: Not implemented yet!\n");

		// Get the string from the inorder traversal
		string record = avl->preOrder();

		// Convert record (a string) to wxRecord (a wxWidget string)
		wxString wxRecord(record.c_str(), wxConvUTF8);

		// Display the string in the MainEditBox
		MainEditBox->AppendText(wxRecord);
	}

void ProjectFrame::OnAVL_Postorder(wxCommandEvent& event)
	{
		// Clear the MainEditBox
		MainEditBox->Clear();

		MainEditBox->AppendText("\t\tAVL_Postorder: Not implemented yet!\n");

		// Get the string from the inorder traversal
		string record = avl->postOrder();

		// Convert record (a string) to wxRecord (a wxWidget string)
		wxString wxRecord(record.c_str(), wxConvUTF8);

		// Display the string in the MainEditBox
		MainEditBox->AppendText(wxRecord);
	}

void ProjectFrame::OnAVL_Delete(wxCommandEvent& event)
	{  MainEditBox->Clear();

    // Get song title
    wxString songTitle = wxGetTextFromUser("Enter the song title to delete:", "Delete from AVL Tree");
    if (songTitle.IsEmpty()) {
        MainEditBox->AppendText("No title entered.\n");
        return;
    }

    // Get artist
    wxString artist = wxGetTextFromUser("Enter the artist:", "Delete from AVL Tree");
    if (artist.IsEmpty()) {
        MainEditBox->AppendText("No artist entered.\n");
        return;
    }

    // Combine artist and title if needed (based on your AVL key structure)
    string titleStr = string(songTitle.mb_str());
    string artistStr = string(artist.mb_str());

	if (avl->inOrder().find(titleStr) == string::npos) {
		MainEditBox->AppendText("Error: That title was not found in the AVL Tree.\n");
		return;
	}

    // If your AVL is keyed by song title only:
    avl->remove(titleStr);

    // If AVL needs both (e.g., keyed on artist+title), update your AVLNode and remove logic

    MainEditBox->AppendText("AVL Delete: " + songTitle + " by " + artist + " removed if it existed.\n");
	}

//=======================================================================================
//====================   Definition for the Red-Black Functions      ==========================
//=======================================================================================

void ProjectFrame::OnRB_Inorder(wxCommandEvent& event)
	{
		// Clear the MainEditBox
		MainEditBox->Clear();

		MainEditBox->AppendText("\t\tRB_Inorder: Not implemented yet!\n");

		// Get the string from the inorder traversal
		string record = rb->inOrder();

		// Convert record (a string) to wxRecord (a wxWidget string)
		wxString wxRecord(record.c_str(), wxConvUTF8);

		// Display the string in the MainEditBox
		MainEditBox->AppendText(wxRecord);
	}

void ProjectFrame::OnRB_Preorder(wxCommandEvent& event)
	{
		// Clear the MainEditBox
		MainEditBox->Clear();

		MainEditBox->AppendText("\t\tRB_Preorder: Not implemented yet!\n");

		// Get the string from the inorder traversal
		string record = rb->preOrder();

		// Convert record (a string) to wxRecord (a wxWidget string)
		wxString wxRecord(record.c_str(), wxConvUTF8);

		// Display the string in the MainEditBox
		MainEditBox->AppendText(wxRecord);
	}

void ProjectFrame::OnRB_Postorder(wxCommandEvent& event)
	{
		// Clear the MainEditBox
		MainEditBox->Clear();

		MainEditBox->AppendText("\t\tRB_Postorder: Not implemented yet!\n");

		// Get the string from the inorder traversal
		string record = rb->postOrder();

		// Convert record (a string) to wxRecord (a wxWidget string)
		wxString wxRecord(record.c_str(), wxConvUTF8);

		// Display the string in the MainEditBox
		MainEditBox->AppendText(wxRecord);
	}

void ProjectFrame::OnRB_Delete(wxCommandEvent& event)
	{
		// Clear the MainEditBox
		MainEditBox->Clear();

		// Prompt for song title
		wxString wxTitle = wxGetTextFromUser("Enter the song title to delete:", "Delete from Red-Black Tree");
		if (wxTitle.IsEmpty()) {
			MainEditBox->AppendText("No song title entered.\n");
			return;
		}

		// Prompt for artist
		wxString wxArtist = wxGetTextFromUser("Enter the artist:", "Delete from Red-Black Tree");
		if (wxArtist.IsEmpty()) {
			MainEditBox->AppendText("No artist entered.\n");
			return;
		}

		// Convert to std::string
		string titleStr = string(wxTitle.mb_str());
		string artistStr = string(wxArtist.mb_str());

		// Optional: check if title exists before deleting
		if (rb->inOrder().find(titleStr) == string::npos) {
			MainEditBox->AppendText("That title was not found in the Red-Black Tree.\n");
			return;
		}

		// Try deletion
		try {
			rb->remove(titleStr);  // Assuming rb->remove uses title as key
			MainEditBox->AppendText("RB Delete: " + wxTitle + " by " + wxArtist + " removed if it existed.\n");
		} catch (...) {
			MainEditBox->AppendText("Error: Could not delete from Red-Black Tree.\n");
		}
	}

//=======================================================================================
//====================   Definition for the SPLAY Functions      ==========================
//=======================================================================================

void ProjectFrame::OnSPLAY_Inorder(wxCommandEvent& event)
	{
		// Clear the MainEditBox
		MainEditBox->Clear();

		MainEditBox->AppendText("\t\tSPLAY_Inorder: Not implemented yet!\n");

		// Get the string from the inorder traversal
		string record = splay->inOrder();

		// Convert record (a string) to wxRecord (a wxWidget string)
		wxString wxRecord(record.c_str(), wxConvUTF8);

		// Display the string in the MainEditBox
		MainEditBox->AppendText(wxRecord);
	}

void ProjectFrame::OnSPLAY_Preorder(wxCommandEvent& event)
	{
		// Clear the MainEditBox
		MainEditBox->Clear();

		MainEditBox->AppendText("\t\tSPLAY_Preorder: Not implemented yet!\n");

		// Get the string from the inorder traversal
		string record = splay->preOrder();

		// Convert record (a string) to wxRecord (a wxWidget string)
		wxString wxRecord(record.c_str(), wxConvUTF8);

		// Display the string in the MainEditBox
		MainEditBox->AppendText(wxRecord);
	}

void ProjectFrame::OnSPLAY_Postorder(wxCommandEvent& event)
	{
		// Clear the MainEditBox
		MainEditBox->Clear();

		MainEditBox->AppendText("\t\tSPLAY_Postorder: Not implemented yet!\n");

		// Get the string from the inorder traversal
		string record = splay->postOrder();

		// Convert record (a string) to wxRecord (a wxWidget string)
		wxString wxRecord(record.c_str(), wxConvUTF8);

		// Display the string in the MainEditBox
		MainEditBox->AppendText(wxRecord);
	}

void ProjectFrame::OnSPLAY_Delete(wxCommandEvent& event)
	{
		// Clear the MainEditBox
		MainEditBox->Clear();
		MainEditBox->AppendText("\t\tSPLAY_Delete: Not implemented yet!\n");

		wxString title = wxGetTextFromUser("Enter title to delete:");
		string strTitle = string(title.mb_str());

		string result = splay->deleteNode(strTitle);  // This returns a string

		wxString wxRecord(result.c_str(), wxMBConvUTF8());
		MainEditBox->AppendText(wxRecord);
	}

//=======================================================================================
//====================   Definition for the MaxHeap Functions      ==========================
//=======================================================================================

void ProjectFrame::OnMaxHeap_Display(wxCommandEvent& event) {
	MainEditBox->Clear();
	string output = maxheap->printHeap();
	wxString wxOutput(output.c_str(), wxConvUTF8);
	MainEditBox->AppendText(wxOutput);
}

void ProjectFrame::OnMaxHeap_Delete(wxCommandEvent& event) {
	MainEditBox->Clear();
	try {
		HeapNodeMax max = maxheap->extractMax();
		string output = "Deleted Max Node:\n" + max.getData();
		MainEditBox->AppendText(wxString(output.c_str(), wxConvUTF8));
	} catch (exception& e) {
		MainEditBox->AppendText("Heap is empty. Nothing to delete.\n");
	}
}

void ProjectFrame::OnMaxHeap_Sort(wxCommandEvent& event) {
	MainEditBox->Clear();

	if (maxheap->isEmpty()) {
		MainEditBox->AppendText("MaxHeap is empty. Nothing to sort.\n");
		return;
	}

	MainEditBox->AppendText("MaxHeap Sorted Order (descending by month #):\n");

	// Copy the heap so we don't alter the original
	MaxBinaryHeap tempHeap = *maxheap;

	while (!tempHeap.isEmpty()) {
		HeapNodeMax maxNode = tempHeap.extractMax();
		MainEditBox->AppendText(wxString(maxNode.getData().c_str(), wxConvUTF8));
	}
}

//=======================================================================================
//====================   Definition for the MinHeap Functions      ==========================
//=======================================================================================

void ProjectFrame::OnMinHeap_Display(wxCommandEvent& event) {
	MainEditBox->Clear();
	string output = minheap->printHeap();
	wxString wxOutput(output.c_str(), wxConvUTF8);
	MainEditBox->AppendText(wxOutput);
}

void ProjectFrame::OnMinHeap_Delete(wxCommandEvent& event) {
	MainEditBox->Clear();
	try {
		HeapNode min = minheap->extractMin();
		string output = "Deleted Min Node:\n" + min.getData();
		MainEditBox->AppendText(wxString(output.c_str(), wxConvUTF8));
	} catch (exception& e) {
		MainEditBox->AppendText("Heap is empty. Nothing to delete.\n");
	}
}

void ProjectFrame::OnMinHeap_Sort(wxCommandEvent& event) {
	MainEditBox->Clear();

	if (minheap->isEmpty()) {
		MainEditBox->AppendText("MinHeap is empty. Nothing to sort.\n");
		return;
	}

	MainEditBox->AppendText("MinHeap Sorted Order (ascending by month #):\n");

	// Copy the heap so we don't alter the original
	MinBinaryHeap tempHeap = *minheap;

	while (!tempHeap.isEmpty()) {
		HeapNode minNode = tempHeap.extractMin();
		MainEditBox->AppendText(wxString(minNode.getData().c_str(), wxConvUTF8));
	}
}

//=======================================================================================
//====================   Definition for the Set Functions      ==========================
//=======================================================================================

void ProjectFrame::OnSetA_Display(wxCommandEvent& event) {
	MainEditBox->Clear();
	string output = setA->printSet();
	MainEditBox->AppendText(wxString(output.c_str(), wxConvUTF8));
}

void ProjectFrame::OnSetB_Display(wxCommandEvent& event) {
	MainEditBox->Clear();
	string output = setB->printSet();
	MainEditBox->AppendText(wxString(output.c_str(), wxConvUTF8));
}

void ProjectFrame::OnSetIntersection_Display(wxCommandEvent& event) {
	MainEditBox->Clear();
	string output = setIntersection->printSet();
	MainEditBox->AppendText(wxString(output.c_str(), wxConvUTF8));
}

void ProjectFrame::OnSetA_Delete(wxCommandEvent& event) {
	MainEditBox->Clear();
	wxString title = wxGetTextFromUser("Enter song title to delete from Set A:");
	if (!title.IsEmpty()) {
		setA->remove(string(title.mb_str()));
		MainEditBox->AppendText("Deleted (if existed) from Set A.\n");
	}
}

void ProjectFrame::OnSetB_Delete(wxCommandEvent& event) {
	MainEditBox->Clear();
	wxString title = wxGetTextFromUser("Enter song title to delete from Set B:");
	if (!title.IsEmpty()) {
		setB->remove(string(title.mb_str()));
		MainEditBox->AppendText("Deleted (if existed) from Set B.\n");
	}
}

//=======================================================================================
//====================   Definition for the About & Help Functions      ==========================
//=======================================================================================

void ProjectFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("Data Structures Project\n\nAuthor: Jayden Cummins\nID: 400013734",
                 "About", wxOK | wxICON_INFORMATION);
	}

void ProjectFrame::OnHelp(wxCommandEvent& event) {
    wxMessageBox("Use the menu to perform actions on the data structures:\n\n"
                 "- File: Load or save catalogs\n"
                 "- Trees: Insert/delete/view songs\n"
                 "- Set A/B: Manage song sets\n\n"
                 "Use the 'Display' box to see current data.",
                 "Help", wxOK | wxICON_QUESTION);
	}
