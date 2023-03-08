#include <stdio.h>
#include <string.h>
#include <exception>
#include <fstream>
#include <vector>
#include <set>
#include <map>
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
#include "TGraph.h"

#include "TGraphErrors.h"

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

// struct OneCubeLY{
//     double LY;
//     int x;
//     int y;
//     int z;
// };

// class CubeLY{
// public:
//     double GetMaxLY(){
//         return allLightYeld.back().key;
//     }
// private:
//     map<double, OneCubeLY> allLightYeld;
// }


int main ()
{
    int febTrigger = 12;
    int FEBs[19] = {0,1,2,3,4,8,9,10,11,12,16,17,18,19,20,24,25,26,27};
    // if (febTrigger == 28) 
    //  int FEBs[19] = {0,1,2,3,4,8,9,10,11,16,17,18,19,20,24,25,26,27,28};
    int NumberOfEB = 30;
    
    vector<string> vFileNames;
    string sFileName;
    ifstream fList("febs_files_list.list");
    while (!fList.eof()) {
        fList >> sFileName;
        vFileNames.push_back(sFileName);
    }
    fList.close();

    ofstream foutput("outputOfProtonLY.txt");
    
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
  
    int minEn = (int)nentries[0];
    for(int i = 0; i < NumberOfEB; i++){
        if(nentries[i] < minEn && nentries[i]>0){
            minEn = (int)nentries[i];
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
            temp++;
        }
        fmap.close();
       }
  }
  
  TH2F *EventsMap_EnergyDeposit = new TH2F("EnergyDeposit_2D","EnergyDeposit_2D",  48,(int)0,(int)48, 50,(int)0,(int)1000);
  TH1F *Events_EnergyDeposit = new TH1F("EnergyDeposit","EnergyDeposit",  48,(int)0,(int)48);

  TH1F *ProtonStopLY = new TH1F("ProtonStopLY","ProtonStopLY",  300,(int)300,(int)1200);

  TDirectory *events2D = wfile.mkdir("events2D");
  int NumberEvDis = 25000;

  TDirectory *events2D_LY = wfile.mkdir("events2DL_Y");
  
  ostringstream sEventnum;
  string sEvent;

  TH1F *events2D_LY_XZ_YZ[48];
  for (Int_t ih=0; ih < 48;ih++){
    sEventnum.str("");
    sEventnum << ih;
    sEvent = "event_XZ&YZ_LY"+sEventnum.str();
    events2D_LY_XZ_YZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(), 70,(int)0,(int)1000);
  }

  Double_t energyDep[48];
  Double_t energyDepXZ[48];
  Double_t energyDepYZ[48];
  Int_t eventNum=0;
  
  bool LargehitTimeDif = 0;

  TCanvas *c1 = new TCanvas("c1","c1", 1480, 1160);
  bool SpillMised = false;
  for (Int_t subSpill = 0; subSpill<minEn; subSpill++) {
  //for (Int_t subSpill = 0; subSpill<155; subSpill++) {
        Int_t SpillNumber = subSpill;
        
        cout << "Getting Spill Number " << SpillNumber + 1 << endl;
        for (int ik = 0; ik < 19; ik++){
            FEBtree[FEBs[ik]]->GetEntry(SpillNumber);
            if (FEB[FEBs[ik]].SpillTag->back() != SpillNumber + 1){
                break;
            }
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
            if (FEB[febTrigger].hitTimeDif->at(TOFtrigger) > 0 && FEB[febTrigger].hitsChannel->at(TOFtrigger) == 1){

                bool triggerDisplay = false;
                LargehitTimeDif = 0;
                Double_t CrossTalk = 0;
                Int_t GTindex[2] = {0,0};
                for (int ik = 0; ik < 48; ik++ ){
                    energyDep[ik] = 0;
                    energyDepXZ[ik] = 0;
                    energyDepYZ[ik] = 0;
                }
                for (int i = 0; i < 19; i++){
                    if (FEBs[i]!=febTrigger){
                        
                        auto bounds=std::equal_range (FEB[FEBs[i]].GTrigTag->begin(), FEB[FEBs[i]].GTrigTag->end(), FEB[febTrigger].GTrigTag->at(TOFtrigger));
                        GTindex[0] = bounds.first - FEB[FEBs[i]].GTrigTag->begin();
                        GTindex[1] = bounds.second - FEB[FEBs[i]].GTrigTag->begin();
            
                        for (int check = GTindex[0]; check <  GTindex[1]; check++){
                            if ( (FEB[febTrigger].hitTimefromSpill->at(TOFtrigger) - FEB[FEBs[i]].hitTimefromSpill->at(check)) > 40 &&
                                (FEB[febTrigger].hitTimefromSpill->at(TOFtrigger) - FEB[FEBs[i]].hitTimefromSpill->at(check)) < 120){
                                 if (FEB[FEBs[i]].hitTimeDif->at(check) > 50)
                                     LargehitTimeDif = 1;
                                if ( FEBs[i] == 0 || FEBs[i] == 16){
                                    if (!triggerDisplay){
                                        triggerDisplay = true;
                                        //cout<<"Trigger time = "<< FEB[febTrigger].hitLeadTime->at(TOFtrigger)<<endl;
                                    }
                                } else if ( FEBs[i] == 1 || FEBs[i] == 2 || FEBs[i] == 17 || FEBs[i] ==24){
                                    if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000) {
                                        energyDep[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                        energyDepYZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                    }
                                    if (MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] == 0 || MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] == 7){
                                        CrossTalk  += FEB[FEBs[i]].hitCharge_pe->at(check);
                                    }
                                } else {
                                    if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000){
                                        energyDep[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                        energyDepXZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                    }
                                    if ((int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] == 0 || (int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] == 23){
                                        CrossTalk  += FEB[FEBs[i]].hitCharge_pe->at(check);
                                    }
                                }
                            }
                        }
                    }
                }
                double extraSumm = 0;
            
                /*for (int ik = 46; ik < 48; ik++ ){
                    extraSumm += energyDep[ik];
                }*/

                for (int ik = 0; ik < 40; ik++ ){
                    if (energyDepXZ[ik] > 5 && energyDepXZ[ik+2] > 5 && energyDepXZ[ik+4] > 5 && energyDepXZ[ik+6] > 5 &&
                        energyDepXZ[ik+1] < 5 && energyDepXZ[ik+3] < 5 && energyDepXZ[ik+5] < 5 && energyDepXZ[ik+7] < 5){
                        LargehitTimeDif = 1;
                    }
                    if (energyDepYZ[ik] > 5 && energyDepYZ[ik+2] > 5 && energyDepYZ[ik+4] > 5 && energyDepYZ[ik+6] > 5 &&
                        energyDepYZ[ik+1] < 5 && energyDepYZ[ik+3] < 5 && energyDepYZ[ik+5] < 5 && energyDepYZ[ik+7] < 5){
                        LargehitTimeDif = 1;
                    }
                }

            if ( extraSumm < 20){

                if ( LargehitTimeDif == 0) {
                    c1->Clear();
                if (CrossTalk < 60){

                    foutput<<eventNum<< " ";
                    for (int ik = 0; ik < 48; ik++ ){
                        if (energyDep[ik]>40){
                            events2D_LY_XZ_YZ[ik]->Fill(energyDep[ik],1);
                            EventsMap_EnergyDeposit->Fill(ik,energyDep[ik],1);
                            Events_EnergyDeposit->Fill(ik,energyDep[ik]);
                        }
                        foutput << energyDep[ik] << " "; 
                    } 
                    auto it = *max_element(std::begin(energyDep), std::end(energyDep));
                    ProtonStopLY-> Fill(it); 

                    foutput << endl;
                }
            }
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

  EventsMap_EnergyDeposit->GetYaxis()->SetTitle("LY [p.e.] (X+Y fiber)");
  EventsMap_EnergyDeposit->GetXaxis()->SetTitle("Z [cm]");
  EventsMap_EnergyDeposit->Write();

  Events_EnergyDeposit->Write();

  ProtonStopLY-> GetYaxis()->SetTitle("N");
  ProtonStopLY-> GetXaxis()->SetTitle("LY [p.e.] (X+Y fiber)");
  ProtonStopLY-> Write();

  events2D_LY -> cd(); //here
  double LYpeaks[48];
  double LYerrorsY[48];
  double LYerrorsX[48];
  double LYki[48];
  Double_t vpar[3];
  TF1 *fit;
  for (int ik = 0; ik < 48; ik++){
    Double_t fitLin2[2];
    fit = new TF1("fit","gaus",60,140);    

    events2D_LY_XZ_YZ[ik]->Fit("fit","MQER+");
    fit->GetParameters(&vpar[0]);
    LYpeaks[ik] = vpar[1];
    LYerrorsY[ik] = vpar[2];
    LYerrorsX[ik] = 0;
    LYki[ik] = ik;
    events2D_LY_XZ_YZ[ik]-> GetYaxis()->SetTitle("N");
    events2D_LY_XZ_YZ[ik]-> GetXaxis()->SetTitle("LY [p.e.] (X+Y fiber)");
    events2D_LY_XZ_YZ[ik]->Draw();
    events2D_LY_XZ_YZ[ik]->Write();
  }
  TGraph graph(44);

  for (int ik = 0; ik < 48; ik++){
    cout<< LYpeaks[ik]<< " " ;
    graph.SetPoint(ik, ik, LYpeaks[ik]);
  }

     graph.SetMarkerStyle(21);
     graph.SetMarkerStyle(2);
    
     graph.GetYaxis()->SetTitle("LY [p.e.] (X+Y fiber)");
     graph.GetXaxis()->SetTitle("Z [cm]");
     graph.Draw("APL");
     graph.Write();

     auto ge = new TGraphErrors(48, LYki, LYpeaks, LYerrorsX, LYerrorsY);
     ge->GetYaxis()->SetTitle("LY [p.e.] (X+Y fiber)");
     ge->GetXaxis()->SetTitle("Z [cm]");
     ge->Draw("APL");
     ge->Write();
     wfile.Close();
     FileInput->Close();
     return 0;
}
