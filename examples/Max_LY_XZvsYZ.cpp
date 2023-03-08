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
#include <TProfile.h>

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
  
  return result;
}

int main ()
{
    
    int NumberOfEB = 30;
    int febTrigger = 12;
    int FEBs[19] = {0,1,2,3,4,8,9,10,11,12,16,17,18,19,20,24,25,26,27};
    
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
    rootFileOutput+="_LY_xz_yz.root";
    cout << rootFileInput<<endl;
    
    TFile *FileInput = new TFile(rootFileInput.c_str());
    TH2F *EventsMap_ToT_PE = new TH2F("All_Protons_PE_From_ToT","All_Protons_PE_From_ToT",50,0,180,50,0,180);
    TH2F *EventsMap_ToT_PE_muons = new TH2F("All_Muons_PE_From_ToT","All_Muons_PE_From_ToT",50,0,180,50,0,180);
    TH2F *EventsMap_HG_PE_muons = new TH2F("All_Muons_PE_From_HG","All_Muons_PE_From_HG",50,0,180,50,0,180);
    TH2F *EventsMap_ToT = new TH2F("All_Protons_ToT","All_Protons_ToT",20,0,50,20,0,50);
    TH2F *EventsMap_AmplHG = new TH2F("All_Protons_PE_From_HG","All_Protons_PE_From_HG",50,0,800,50,0,800);
    TH2F *EventsMap_AmplLG = new TH2F("All_Protons_PE_From_LG","All_Protons_PE_From_LG",50,0,800,50,0,800);

    TH1F *EventsTimeTrigger = new TH1F("EventsTimeTrigger","EventsTimeTrigger",180,0,180);
    TH1F *EventsSigma = new TH1F("Events45-55","Events45-55",50,0,100);

    ostringstream sKube;
    string sKb;
    int NumberOfCubes = 10000;
    TH2F *LYofKube[NumberOfCubes];

    for (int ikube = 0; ikube <16; ikube++){
      sKube.str("");
      sKube << ikube;
      sKb =  "LY_of_Kube_" + sKube.str();
      LYofKube[ikube] = new TH2F(sKb.c_str(),sKb.c_str(),50,0,180,50,0,180);
    }
    
    
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
        }
    }

    vector<double> XZmax;
    vector<double> XZmaxToT;
    vector<double> YZmax; 
    vector<double> YZmaxToT; 

    vector<double> XZmaxHG;
    vector<double> YZmaxHG; 
    vector<double> XZmaxLG;
    vector<double> YZmaxLG; 

    double LY_position[48][24][8];
    int Position[48][24][8][2];
    double HG_position[48][24][8];
    for (int ik = 0; ik < 48; ik++){
      for (int ij = 0; ij < 8; ij++){
        for (int ih = 0; ih < 24; ih++){
          LY_position[ik][ih][ij] = 0;
          HG_position[ik][ih][ij] = 0;
          Position[ik][ih][ij][0] = 0;
          Position[ik][ih][ij][1] = 0;
        }
      }
    }
  
    double minEn = nentries[0];
    for(int i = 0; i < NumberOfEB; i++){
        if(nentries[i] < minEn && nentries[i]>0){
            minEn = 890;
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
        }
        fmap.close();
       }
  }

  
  ostringstream sEventnum;
  string sEvent;
  
  Int_t eventNum=0;


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
        }
        if (!SpillMised){
          for ( int TOFtrigger = 0; TOFtrigger < FEB[febTrigger].FEBSN->size(); TOFtrigger++){
            int countXY = 0;
            if (FEB[febTrigger].hitsChannel->at(TOFtrigger) == 2){
              double triggerTime = FEB[febTrigger].hitLeadTime->at(TOFtrigger);
              Int_t GTindex[2] = {0,0};
              for (int i = 0; i < 19; i++){
                if (FEBs[i]!=febTrigger){
                  auto bounds=std::equal_range (FEB[FEBs[i]].GTrigTag->begin(), FEB[FEBs[i]].GTrigTag->end(), FEB[febTrigger].GTrigTag->at(TOFtrigger));
                  GTindex[0] = bounds.first - FEB[FEBs[i]].GTrigTag->begin();
                  GTindex[1] = bounds.second - FEB[FEBs[i]].GTrigTag->begin();
            
                  for (int check = GTindex[0]; check <  GTindex[1]; check++){
                    if ( FEBs[i] == 0 || FEBs[i] == 16){
                      if (FEB[FEBs[i]].hitTimeDif->at(check)>7){
                        countXY++;
                      }
                    } else if ( FEBs[i] == 1 || FEBs[i] == 2 || FEBs[i] == 17 || FEBs[i] ==24){
                      if (abs(triggerTime - FEB[FEBs[i]].hitLeadTime->at(check)) <=100 && abs(triggerTime - FEB[FEBs[i]].hitLeadTime->at(check)) > 95 ){
                        YZmax.push_back(FEB[FEBs[i]].hitCharge_pe->at(check));
                        if (FEB[FEBs[i]].hitTimeDif->at(check) < 100) {
                          YZmaxHG.push_back(FEB[FEBs[i]].hitHG_pe->at(check));
                          YZmaxToT.push_back(FEB[FEBs[i]].hitTimeDif->at(check));
                          YZmaxLG.push_back(FEB[FEBs[i]].hitLG_pe->at(check));
                          LY_position[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]][0][MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] = FEB[FEBs[i]].hitCharge_pe->at(check);
                          HG_position[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]][0][MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] = FEB[FEBs[i]].hitHG_pe->at(check);
                          //Position[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]][0][MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] = 
                          EventsTimeTrigger->Fill(abs(triggerTime - FEB[FEBs[i]].hitLeadTime->at(check)),1);
                        }
                      }
                    } else {
                      if (abs(triggerTime - FEB[FEBs[i]].hitLeadTime->at(check)) <=100 && abs(triggerTime - FEB[FEBs[i]].hitLeadTime->at(check)) > 95){
                        XZmax.push_back(FEB[FEBs[i]].hitCharge_pe->at(check));
                        if (FEB[FEBs[i]].hitTimeDif->at(check) < 100){
                          XZmaxHG.push_back(FEB[FEBs[i]].hitHG_pe->at(check));
                          XZmaxToT.push_back(FEB[FEBs[i]].hitTimeDif->at(check));
                          XZmaxLG.push_back(FEB[FEBs[i]].hitLG_pe->at(check));
                          LY_position[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]][MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]][0] = FEB[FEBs[i]].hitCharge_pe->at(check);
                          HG_position[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]][MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]][0] = FEB[FEBs[i]].hitHG_pe->at(check);
                          EventsTimeTrigger->Fill(abs(triggerTime - FEB[FEBs[i]].hitLeadTime->at(check)),1);
                        }
                      }
                    }
                  }
                }
              }
              if (YZmax.size() > 7 && XZmax.size() > 7 ){
                double maxElementYZ = *std::max_element(YZmax.begin(), YZmax.end());
                double maxElementYZToT = *std::max_element(YZmaxToT.begin(), YZmaxToT.end());
                double maxElementXZ = *std::max_element(XZmax.begin(), XZmax.end());
                double maxElementXZToT = *std::max_element(XZmaxToT.begin(), XZmaxToT.end());

                double maxElementYZHG = *std::max_element(YZmaxHG.begin(), YZmaxHG.end());
                double maxElementXZHG = *std::max_element(XZmaxHG.begin(), XZmaxHG.end());

                double maxElementYZLG = *std::max_element(YZmaxLG.begin(), YZmaxLG.end());
                double maxElementXZLG = *std::max_element(XZmaxLG.begin(), XZmaxLG.end());
                //cout << endl <<  maxElementYZ << "--"<< maxElementYZHG<< " " << maxElementXZ <<endl <<endl;

                double position8[48];
                double position24[48];

                for (int ik = 0; ik < 48; ik++){
                  //LY_position[48][24][8];
                  double maxelements8 = LY_position[ik][0][0];
                  double maxelements8HG = HG_position[ik][0][0];
                  position8[ik] = 0;
                  position24[ik] = 0;
                  int count8 = 0;
                  for (int ij = 1; ij < 8; ij++){
                    if (LY_position[ik][0][ij] > maxelements8){
                      maxelements8 = LY_position[ik][0][ij];
                      maxelements8HG = HG_position[ik][0][ij];
                      position8[ik] = ij;
                    }
                    /*if (HG_position[ik][0][ij] > maxelements8HG){
                      maxelements8HG = HG_position[ik][0][ij];
                    }*/

                    if (LY_position[ik][0][ij] > 5)
                      count8++;
                  }
                  double maxelements24 = LY_position[ik][0][0];
                  double maxelements24HG = HG_position[ik][0][0];
                  int count24 = 0;
                  for (int ih = 0; ih < 24; ih++){
                    if (LY_position[ik][ih][0] > maxelements24){
                      maxelements24 = LY_position[ik][ih][0];
                      maxelements24HG = HG_position[ik][ih][0];
                      position24[ik] = ih;
                    }
                    /*if (HG_position[ik][ih][0] > maxelements24HG){
                      maxelements24HG = HG_position[ik][ih][0];
                    }*/
                    if (LY_position[ik][ih][0] > 5)
                      count24++;
                  }
                  if (maxelements24 > 5 && maxelements8 > 5 && maxelements24 + maxelements8 >20 && countXY<=5 && maxelements24/maxelements8 > 0.3 && maxelements24/maxelements8 < 3){
                    EventsMap_ToT_PE_muons->Fill(maxelements24,maxelements8,1);
                    if (maxelements24HG + maxelements8HG >20)
                      EventsMap_HG_PE_muons->Fill(maxelements24HG,maxelements8HG,1);
                    if(position24[ik]>0 && position8[ik] > 0 && ik >0)
                      //LYofKube[(int)((position24[ik])*(position8[ik])*(ik))]->Fill(maxelements24,maxelements8,1);
                    /*if (ik<3 && ik>0 && position8[ik] > 3 && position8[ik] < 6 && position24[ik] >=8  && position24[ik] < 24)
                      LYofKube[(int)((position24[ik]-8)*(position8[ik]-3))]->Fill(maxelements24,maxelements8,1);*/
                    if (maxelements8>45 && maxelements8<55){
                      EventsSigma->Fill(maxelements24,1);
                    }
                  }
                }
                YZmax.clear();
                XZmax.clear();
                YZmaxToT.clear();
                XZmaxToT.clear();
                YZmaxHG.clear();
                XZmaxHG.clear();
                YZmaxLG.clear(); 
                XZmaxLG.clear();
                for (int ik = 0; ik < 48; ik++){
                  for (int ij = 0; ij < 8; ij++){
                    for (int ih = 0; ih < 24; ih++){
                      LY_position[ik][ih][ij] = 0;
                    }
                  }
                }

                if (maxElementYZ>5 && maxElementXZ > 5 && maxElementYZToT<100 && maxElementXZToT<100 && maxElementYZToT < 100 && maxElementXZToT < 100) {
                  EventsMap_ToT_PE->Fill(maxElementYZ,maxElementXZ,1);
                  EventsMap_ToT->Fill(maxElementYZToT,maxElementXZToT,1);
                  EventsMap_AmplHG->Fill(maxElementYZHG,maxElementXZHG,1);
                  EventsMap_AmplLG->Fill(maxElementYZLG,maxElementXZLG,1);
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
  EventsMap_ToT_PE->GetYaxis()->SetTitle("YZ[pe]");
  EventsMap_ToT_PE->GetXaxis()->SetTitle("XZ[pe]");
  EventsMap_ToT_PE->Draw("colorz");
  EventsMap_ToT_PE->Write();

  EventsMap_ToT->GetYaxis()->SetTitle("YZ[2.5ns]");
  EventsMap_ToT->GetXaxis()->SetTitle("XZ[2.5ns]");
  EventsMap_ToT->Draw("colorz");
  EventsMap_ToT->Write();

  EventsMap_AmplHG->GetYaxis()->SetTitle("YZ[pe]");
  EventsMap_AmplHG->GetXaxis()->SetTitle("XZ[pe]");
  EventsMap_AmplHG->Draw("colorz");
  EventsMap_AmplHG->Write();

  EventsMap_AmplLG->GetYaxis()->SetTitle("YZ[pe]");
  EventsMap_AmplLG->GetXaxis()->SetTitle("XZ[pe]");
  EventsMap_AmplLG->Draw("colorz");
  EventsMap_AmplLG->Write();

  EventsMap_ToT_PE_muons->GetYaxis()->SetTitle("YZ[pe]");
  EventsMap_ToT_PE_muons->GetXaxis()->SetTitle("XZ[pe]");
  EventsMap_ToT_PE_muons->Write();

  EventsMap_HG_PE_muons->GetYaxis()->SetTitle("YZ[pe]");
  EventsMap_HG_PE_muons->GetXaxis()->SetTitle("XZ[pe]");
  EventsMap_HG_PE_muons->Write();

  TProfile *prof = EventsMap_ToT_PE_muons->ProfileX();
  prof->GetYaxis()->SetTitle("YZ[pe]");
  prof->GetXaxis()->SetTitle("XZ[pe]");
  TF1 *f = new TF1("f","pol1",10,100);
  prof->Fit("f","MER");
  prof->Write();

  EventsSigma->GetXaxis()->SetTitle("XZ[pe]");
  EventsSigma->GetXaxis()->SetTitle("N");
  EventsSigma->Write();
  EventsTimeTrigger->Write();
  TDirectory *LY_kube = wfile.mkdir("LY_of_cube");
  LY_kube->cd();
  for (int ikube = 0; ikube <NumberOfCubes; ikube++){
    if (LYofKube[ikube]->GetEntries()>10)
     LYofKube[ikube]->Write();
  }

  wfile.Close();
  FileInput->Close();
  return 0;
}
