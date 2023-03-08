#include <stdio.h>
#include <string.h>
#include <exception>
#include <fstream>
#include <vector>
#include "TFile.h"
#include "TDirectory.h"
#include "TH1D.h"
#include "TSystem.h"
#include "TMacro.h"
#include <TTree.h>
#include <iostream>
#include <sstream>
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TCanvas.h"
#include <iterator>
#include <algorithm>
#include "TImage.h"
#include "TStyle.h"



using namespace std;


string GetLocation(string str)
{
     
    int i = str.rfind("_Slot_");
    string way = str.substr(0,i);  
    return way;
}

struct vectorsTree
{
  vector<double> *FEBSN;
  vector<double> *SpillTag;
  vector<double> *GTrigTag;
  vector<double> *GTrigTime;
  vector<double> *hitsChannel;
  vector<double> *hitAmpl;
  vector<double> *hitAmplRec;
  vector<double> *hitLGAmpl;
  vector<double> *hitLGAmplRec;
  vector<double> *hitHG_pe;
  vector<double> *hitLG_pe;
  vector<double> *hitToT_pe;
  vector<double> *hitCharge_pe;
  vector<double> *hitLeadTime;
  vector<double> *hitTrailTime;
  vector<double> *hitTimeDif;
  vector<double> *hitTimefromSpill;
  
};

bool isCheckChannel (int FEB, int ch){
  bool result = false;
  if (FEB == 1){
    if (ch == 16 || ch == 17 || ch == 18 || ch == 19 ){
      result = true;
    }
  } else if(FEB == 2){
    if (ch == 16 || ch == 17 || ch == 18 || ch == 19 ){
      result = true;
    }
  } else if(FEB == 3){
    if (ch == 48 || ch == 49 || ch == 50 || ch == 51 ){
      result = true;
    }
  } else if(FEB == 9){
    if (ch == 48 || ch == 49 || ch == 50 || ch == 51 ){
      result = true;
    }
  }
  return result;
}

int main ()
{
    
    int NumberOfEB = 30;
    int febTrigger = 12;
    int FEBs[19] = {0,1,2,3,4,8,9,10,11,12,16,17,18,19,20,24,25,26,27};
    //int FEBs[19] = {0,1,2,3,4,8,9,10,11,16,17,18,19,20,24,25,26,27,28};
    
    vector<string> vFileNames;
    string sFileName;
    ifstream fList("febs_files_list.list");
    while (!fList.eof()) {
        fList >> sFileName;
        vFileNames.push_back(sFileName);
    }
    fList.close();
    
    string rootFileInput=GetLocation(vFileNames[0].c_str());
    string rootFileOutput=GetLocation (vFileNames[0].c_str());
    rootFileInput+="_all_reconstructed.root";
    //rootFileInput+="_all.root";
    rootFileOutput+="_event_display.root";
    cout << rootFileInput<<endl;
    
    TFile *FileInput = new TFile(rootFileInput.c_str());
    
    vectorsTree FEB[NumberOfEB];
    
    for (Int_t i=0;i<NumberOfEB;i++){
        FEB[i].FEBSN=0;
        FEB[i].SpillTag=0;
        FEB[i].hitsChannel=0;
        FEB[i].hitAmpl=0;
        FEB[i].hitAmplRec=0;
        FEB[i].hitLeadTime=0;
        FEB[i].GTrigTag=0;
        FEB[i].GTrigTime=0;
        FEB[i].hitLGAmpl=0;
        FEB[i].hitLGAmplRec=0;
        FEB[i].hitTrailTime=0;
        FEB[i].hitTimeDif=0;
        FEB[i].hitTimefromSpill=0;
        
        FEB[i].hitHG_pe=0;
        FEB[i].hitLG_pe=0;
        FEB[i].hitToT_pe=0;
        FEB[i].hitCharge_pe=0;
        
    }
    
    
    TTree *FEBtree[NumberOfEB];
    Long64_t nentries[NumberOfEB];
    std::fill(nentries, nentries + NumberOfEB, 0);
    
    ostringstream sFEBnum;
    string sFEB;
    
    vector<int> FEBnumbers;
    FEBnumbers.clear();
    
    
    for (Int_t ih=0; ih<NumberOfEB; ih++) {
        sFEBnum.str("");
        sFEBnum << ih;
        sFEB = "FEB_"+sFEBnum.str();
        FEBtree[ih] = (TTree*)FileInput->Get(sFEB.c_str());
        if ((TTree*)FileInput->Get(sFEB.c_str())){
            //std::cout<<sFEB<<" ";
            FEBtree[ih]->SetBranchAddress((sFEB+"_SN").c_str(),&FEB[ih].FEBSN);
            FEBtree[ih]->SetBranchAddress((sFEB+"_SpillTag").c_str(),&FEB[ih].SpillTag);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTag").c_str(),&FEB[ih].GTrigTag);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTime").c_str(),&FEB[ih].GTrigTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitsChannel").c_str(),&FEB[ih].hitsChannel);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitAmpl").c_str(),&FEB[ih].hitAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLGAmpl").c_str(),&FEB[ih].hitLGAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLeadTime").c_str(),&FEB[ih].hitLeadTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTrailTime").c_str(),&FEB[ih].hitTrailTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTimeDif").c_str(),&FEB[ih].hitTimeDif);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTimefromSpill").c_str(),&FEB[ih].hitTimefromSpill);
            
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitAmplRecon").c_str(), &FEB[ih].hitAmplRec);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLGAmplRecon").c_str(), &FEB[ih].hitLGAmplRec);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitHG_pe").c_str(), &FEB[ih].hitHG_pe);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLG_pe").c_str(), &FEB[ih].hitLG_pe);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitToT_pe").c_str(), &FEB[ih].hitToT_pe);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitCharge_pe").c_str(), &FEB[ih].hitCharge_pe);
            
            nentries[ih] = FEBtree[ih]->GetEntries();
            FEBtree[ih]->GetEntry(0);
            //std::cout << "Number of events = " <<FEB[ih].FEBSN->size()<<std::endl;
        }
  }
  
    double minEn = nentries[0];
    for(int i = 0; i < NumberOfEB; i++){
        if(nentries[i] < minEn && nentries[i]>0){
            minEn = nentries[i];
        }
    }
    cout << "Number of spills " << minEn << endl;

  TFile wfile(rootFileOutput.c_str(), "recreate");
  cout<<rootFileOutput<<endl;
  
  
  int MapCon[28][2][96];
  for (int iFEB = 0; iFEB<19; iFEB++) {
       if (FEBs[iFEB] != febTrigger){
        sFEBnum.str("");
        sFEBnum << FEBs[iFEB];
        sFEB = "../mapping/" + sFEBnum.str() + ".txt";
        ifstream fmap(sFEB.c_str());
        //cout <<endl<< "FEB "<< FEBs[iFEB]<< " mapping"<<endl;
        int temp=0;
        while (!fmap.eof()) {
            fmap >> temp >> MapCon[FEBs[iFEB]][0][temp] >>MapCon[FEBs[iFEB]][1][temp];
            //cout<<temp<<" "<<MapCon[FEBs[iFEB]][0][temp]<<" "<<MapCon[FEBs[iFEB]][1][temp]<<endl;
        //temp++;
        }
        fmap.close();
       }
  }

  

  TH2F *EventsMap_XY = new TH2F("All_events_map_XY","All_events_map_XY",  24,0,24, 8,0,8);
  TH2F *EventsMap_YZ = new TH2F("All_events_map_YZ","All_events_map_YZ",  48,0,48, 8,0,8);
  TH2F *EventsMap_XZ = new TH2F("All_events_map_XZ","All_events_map_XZ",  24,0,24, 48,0,48);

  TH1F *Avr_LY_particles[18];
  Avr_LY_particles[0] = new TH1F("LY_electrons","LY_electrons", 70,0,200);
  Avr_LY_particles[1] = new TH1F("LY_pions_muons","LY_pions_muons", 50,0,200);
  Avr_LY_particles[2] = new TH1F("LY_protons","LY_protons", 70,0,200);

  Avr_LY_particles[3] = new TH1F("LY_electrons_XZ","LY_electrons_XZ", 70,0,200);
  Avr_LY_particles[4] = new TH1F("LY_pions_muons_XZ","LY_pions_muons_XZ", 50,0,200);
  Avr_LY_particles[5] = new TH1F("LY_protons_XZ","LY_protons_XZ", 70,0,200);

  Avr_LY_particles[6] = new TH1F("LY_electrons_YZ","LY_electrons_YZ", 70,0,200);
  Avr_LY_particles[7] = new TH1F("LY_pions_muons_YZ","LY_pions_muons_YZ", 50,0,200);
  Avr_LY_particles[8] = new TH1F("LY_protons_YZ","LY_protons_YZ", 70,0,200);

  Avr_LY_particles[9] = new TH1F("Average_LY_electrons","Average_LY_electrons", 70,0,200);
  Avr_LY_particles[10] = new TH1F("Average_LY_pions_muons","Average_LY_pions_muons", 50,0,200);
  Avr_LY_particles[11] = new TH1F("Average_LY_protons","Average_LY_protons", 70,0,200);

  Avr_LY_particles[12] = new TH1F("Average_LY_electrons_XZ","Average_LY_electrons_XZ", 70,0,200);
  Avr_LY_particles[13] = new TH1F("Average_LY_pions_muons_XZ","Average_LY_pions_muons_XZ", 50,0,200);
  Avr_LY_particles[14] = new TH1F("Average_LY_protons_XZ","Average_LY_protons_XZ", 70,0,200);

  Avr_LY_particles[15] = new TH1F("Average_LY_electrons_YZ","Average_LY_electrons_YZ", 70,0,200);
  Avr_LY_particles[16] = new TH1F("Average_LY_pions_muons_YZ","Average_LY_pions_muons_YZ", 50,0,200);
  Avr_LY_particles[17] = new TH1F("Average_LY_protons_YZ","Average_LY_protons_YZ", 70,0,200);



  TF1 *fitMuon = new TF1("fitMuon","gaus", 35, 55);
  TF1 *fitProton = new TF1("fitProton","gaus", 50, 90);


  //TDirectory *events2D = wfile.mkdir("events2D");
  
  ostringstream sEventnum;
  string sEvent;
  
  Int_t eventNum=0;
  int channelsCheckFEB1[4] = {16,17,18,19};
  int channelsCheckFEB2[4] = {16,17,18,19};
  int channelsCheckFEB3[4] = {48,49,50,51};
  int channelsCheckFEB9[4] = {48,49,50,51};
  bool LargehitTimeDif = 0;
  double AvrLYforFiber = 0;
  double AvrLYforFiberXZ = 0;
  double AvrLYforFiberYZ = 0;

  TCanvas *c1 = new TCanvas("c1","c1", 1480, 1160);
  bool SpillMised = false;
  for (Int_t subSpill = 0; subSpill<minEn; subSpill++) {
  //for (Int_t subSpill = 0; subSpill<10; subSpill++) {
        Int_t SpillNumber = subSpill;
        
        cout << "Getting Spill Number " << SpillNumber + 1 << endl;
        for (int ik = 0; ik < 19; ik++){
            FEBtree[FEBs[ik]]->GetEntry(SpillNumber);

            if (FEB[FEBs[ik]].SpillTag->size() < 2 ){
                cout << "NULL"<<endl;
                SpillMised = true;
                break;
            } else {
                SpillMised = false;
            }
            //cout << "FEB_"<< FEBs[ik]<< " "<< FEB[FEBs[ik]].hitCharge_pe->size()<<endl;
        }
        if (!SpillMised){
            for ( int TOFtrigger = 0; TOFtrigger < FEB[febTrigger].FEBSN->size(); TOFtrigger++){

              if (FEB[febTrigger].hitTimeDif->at(TOFtrigger) > 0 && FEB[febTrigger].hitsChannel->at(TOFtrigger) != 3){
                    LargehitTimeDif = 0;
                    Int_t GTindex[2] = {0,0};

                    Int_t GTindexCheck1[2] = {0,0};
                    Int_t GTindexCheck2[2] = {0,0};
                    Int_t GTindexCheck3[2] = {0,0};
                    Int_t GTindexCheck9[2] = {0,0};
                    bool cut[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

                    auto boundsCheck1=std::equal_range (FEB[1].GTrigTag->begin(), FEB[1].GTrigTag->end(), FEB[febTrigger].GTrigTag->at(TOFtrigger));
                    GTindexCheck1[0] = boundsCheck1.first - FEB[1].GTrigTag->begin();
                    GTindexCheck1[1] = boundsCheck1.second - FEB[1].GTrigTag->begin();
                    for (int check = GTindexCheck1[0]; check <  GTindexCheck1[1]; check++){
                      if (FEB[1].hitsChannel->at(check) == channelsCheckFEB1[0] && FEB[1].hitCharge_pe->at(check) > 10){
                        cut[0] = true;
                      }
                      if (FEB[1].hitsChannel->at(check) == channelsCheckFEB1[1]){
                        cut[1] = true;
                      }
                      if (FEB[1].hitsChannel->at(check) == channelsCheckFEB1[2]){
                        cut[2] = true;
                      }
                      if (FEB[1].hitsChannel->at(check) == channelsCheckFEB1[3]){
                        cut[3] = true;
                      }
                    }

                    auto boundsCheck2=std::equal_range (FEB[2].GTrigTag->begin(), FEB[2].GTrigTag->end(), FEB[febTrigger].GTrigTag->at(TOFtrigger));
                    GTindexCheck2[0] = boundsCheck2.first - FEB[2].GTrigTag->begin();
                    GTindexCheck2[1] = boundsCheck2.second - FEB[2].GTrigTag->begin();
                    for (int check = GTindexCheck2[0]; check <  GTindexCheck2[1]; check++){
                      if (FEB[2].hitsChannel->at(check) == channelsCheckFEB2[0]){
                        cut[4] = true;
                      }
                      if (FEB[2].hitsChannel->at(check) == channelsCheckFEB2[1]){
                        cut[5] = true;
                      }
                      if (FEB[2].hitsChannel->at(check) == channelsCheckFEB2[2]){
                        cut[6] = true;
                      }
                      if (FEB[2].hitsChannel->at(check) == channelsCheckFEB2[3] && FEB[2].hitCharge_pe->at(check) > 10){
                        cut[7] = true;
                      }
                    }

                    auto boundsCheck3=std::equal_range (FEB[3].GTrigTag->begin(), FEB[3].GTrigTag->end(), FEB[febTrigger].GTrigTag->at(TOFtrigger));
                    GTindexCheck3[0] = boundsCheck3.first - FEB[3].GTrigTag->begin();
                    GTindexCheck3[1] = boundsCheck3.second - FEB[3].GTrigTag->begin();
                    for (int check = GTindexCheck3[0]; check <  GTindexCheck3[1]; check++){
                      if (FEB[3].hitsChannel->at(check) == 48){
                        cut[8] = true;
                      }
                      if (FEB[3].hitsChannel->at(check) == 49){
                        cut[9] = true;
                      }
                      if (FEB[3].hitsChannel->at(check) == 50){
                        cut[10] = true;
                      }
                      if (FEB[3].hitsChannel->at(check) == 51 && FEB[3].hitCharge_pe->at(check) > 10){
                        cut[11] = true;
                      }
                    }

                    auto boundsCheck9=std::equal_range (FEB[9].GTrigTag->begin(), FEB[9].GTrigTag->end(), FEB[febTrigger].GTrigTag->at(TOFtrigger));
                    GTindexCheck9[0] = boundsCheck9.first - FEB[9].GTrigTag->begin();
                    GTindexCheck9[1] = boundsCheck9.second - FEB[9].GTrigTag->begin();
                    for (int check = GTindexCheck9[0]; check <  GTindexCheck9[1]; check++){
                      if (FEB[9].hitsChannel->at(check) == 48 && FEB[9].hitCharge_pe->at(check) > 10){
                        cut[12] = true;
                      }
                      if (FEB[9].hitsChannel->at(check) == 49){
                        cut[13] = true;
                      }
                      if (FEB[9].hitsChannel->at(check) == 50){
                        cut[14] = true;
                      }
                      if (FEB[9].hitsChannel->at(check) == 51){
                        cut[15] = true;
                      }
                    }
                    if (cut[0] == true && cut[1] == true && cut[2] == true && cut[3] == true
                      && cut[4] == true && cut[5] == true && cut[6] == true && cut[7] == true 
                      && cut[8] == true && cut[9] == true && cut[10] == true && cut[11] == true
                      && cut[12] == true && cut[13] == true && cut[14] == true && cut[15] == true){

                      for (int i = 0; i < 19; i++){
                        if (FEBs[i]!=febTrigger){
                        
                        auto bounds=std::equal_range (FEB[FEBs[i]].GTrigTag->begin(), FEB[FEBs[i]].GTrigTag->end(), FEB[febTrigger].GTrigTag->at(TOFtrigger));
                        GTindex[0] = bounds.first - FEB[FEBs[i]].GTrigTag->begin();
                        GTindex[1] = bounds.second - FEB[FEBs[i]].GTrigTag->begin();
            
                        for (int check = GTindex[0]; check <  GTindex[1]; check++){
                            if (abs(FEB[febTrigger].hitTimefromSpill->at(TOFtrigger) - FEB[FEBs[i]].hitTimefromSpill->at(check)) < 100 && isCheckChannel((int)FEBs[i], (int)FEB[FEBs[i]].hitsChannel->at(check))){
                                if (FEB[FEBs[i]].hitTimeDif->at(check) > 100)
                                    LargehitTimeDif = 1;
                                if ( FEBs[i] == 0 || FEBs[i] == 16){
                                    EventsMap_XY->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                } else if ( FEBs[i] == 1 || FEBs[i] == 2 || FEBs[i] == 17 || FEBs[i] ==24){
                                    EventsMap_YZ->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                    if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000 ) {
                                      Avr_LY_particles[(int)FEB[febTrigger].hitsChannel->at(TOFtrigger)]->Fill(FEB[FEBs[i]].hitCharge_pe->at(check));
                                      Avr_LY_particles[(int)FEB[febTrigger].hitsChannel->at(TOFtrigger) + 6]->Fill(FEB[FEBs[i]].hitCharge_pe->at(check));
                                      AvrLYforFiberYZ = AvrLYforFiberYZ + FEB[FEBs[i]].hitCharge_pe->at(check);
                                      AvrLYforFiber = AvrLYforFiber + FEB[FEBs[i]].hitCharge_pe->at(check);
                                    }                            
                                } else {
                                    EventsMap_XZ->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                    if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000 ){
                                      Avr_LY_particles[(int)FEB[febTrigger].hitsChannel->at(TOFtrigger)]->Fill(FEB[FEBs[i]].hitCharge_pe->at(check));
                                      Avr_LY_particles[(int)FEB[febTrigger].hitsChannel->at(TOFtrigger) + 3]->Fill(FEB[FEBs[i]].hitCharge_pe->at(check));
                                      AvrLYforFiberXZ = AvrLYforFiberXZ + FEB[FEBs[i]].hitCharge_pe->at(check);
                                      AvrLYforFiber = AvrLYforFiber + FEB[FEBs[i]].hitCharge_pe->at(check);
                                    }                            
                                }
                            }
                        }
                    }
                  }
                  eventNum++;
            AvrLYforFiberYZ = AvrLYforFiberYZ/8;
            AvrLYforFiberXZ = AvrLYforFiberXZ/8;
            AvrLYforFiber = AvrLYforFiber/16;
            Avr_LY_particles[(int)FEB[febTrigger].hitsChannel->at(TOFtrigger) + 9] -> Fill(AvrLYforFiber);
            Avr_LY_particles[(int)FEB[febTrigger].hitsChannel->at(TOFtrigger) + 12] -> Fill(AvrLYforFiberXZ);
            Avr_LY_particles[(int)FEB[febTrigger].hitsChannel->at(TOFtrigger) + 15] -> Fill(AvrLYforFiberYZ);
            AvrLYforFiber = 0;
            AvrLYforFiberXZ = 0;
            AvrLYforFiberYZ = 0;
            }
            
          }
      }
 
  for (Int_t i=0;i<NumberOfEB;i++){
        FEB[i].FEBSN=0;
        FEB[i].SpillTag=0;
        FEB[i].hitsChannel=0;
        FEB[i].hitAmpl=0;
        FEB[i].hitAmplRec=0;
        FEB[i].hitLeadTime=0;
        FEB[i].GTrigTag=0;
        FEB[i].GTrigTime=0;
        FEB[i].hitLGAmpl=0;
        FEB[i].hitLGAmplRec=0;
        FEB[i].hitTrailTime=0;
        FEB[i].hitTimeDif=0;
        FEB[i].hitTimefromSpill=0;
        
        FEB[i].hitHG_pe=0;
        FEB[i].hitLG_pe=0;
        FEB[i].hitToT_pe=0;
        FEB[i].hitCharge_pe=0;
        
    }
        }    
  }
   wfile.cd();
  EventsMap_XY->Write();
  EventsMap_YZ->Write();
  EventsMap_XZ->Write();
  Avr_LY_particles[0]->Fit("fitMuon","MQER+");
  Avr_LY_particles[3]->Fit("fitMuon","MQER+");
  Avr_LY_particles[6]->Fit("fitMuon","MQER+");

  Avr_LY_particles[1]->Fit("fitMuon","MQER+");
  Avr_LY_particles[4]->Fit("fitMuon","MQER+");
  Avr_LY_particles[7]->Fit("fitMuon","MQER+");

  Avr_LY_particles[2]->Fit("fitProton","MQER+");
  Avr_LY_particles[5]->Fit("fitProton","MQER+");
  Avr_LY_particles[8]->Fit("fitProton","MQER+");

  Avr_LY_particles[9]->Fit("fitMuon","MQER+");
  Avr_LY_particles[12]->Fit("fitMuon","MQER+");
  Avr_LY_particles[15]->Fit("fitMuon","MQER+");

  Avr_LY_particles[10]->Fit("fitMuon","MQER+");
  Avr_LY_particles[13]->Fit("fitMuon","MQER+");
  Avr_LY_particles[16]->Fit("fitMuon","MQER+");

  Avr_LY_particles[11]->Fit("fitProton","MQER+");
  Avr_LY_particles[14]->Fit("fitProton","MQER+");
  Avr_LY_particles[17]->Fit("fitProton","MQER+");

  for (int k =0; k<18; k++){
    Avr_LY_particles[k]->Write();
  }
  
     wfile.Close();
     FileInput->Close();
     return 0;
}
