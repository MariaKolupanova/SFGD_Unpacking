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
#include "TH1F.h"
#include <iostream>
#include <cmath>
#include <numeric>
#include <TSpectrum2.h>


struct Proton{ 
    int par_1,par_2;
    double p_e;
};

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

Double_t fpeaks(Double_t x, Double_t par[5]) {
    //return -par[0]*log(1/(par[1]-x))+par[2]/(x*x-par[3])+par[4];}
     return -par[0]*log(1/(par[1]-x))+par[2]/(x-par[3])+par[4];}
int main ()
{
    vector <Proton> x_z;
    vector <Proton> z_y;
    int febTrigger = 12;
    int FEBs[19] = {0,1,2,3,4,8,9,10,11,12,16,17,18,19,20,24,25,26,27};
    int NumberOfEB = 30;
    vector<string> vFileNames;
    string sFileName;
    ifstream fList("febs_files_list.list");
    while (!fList.eof()) {
        fList >> sFileName;
        vFileNames.push_back(sFileName);
    }
    fList.close();
    ofstream fout("proton_peak.txt");
    string rootFileInput=GetLocation(vFileNames[0].c_str());
    string rootFileOutput=GetLocation (vFileNames[0].c_str());
    //string txtFileFit=GetLocation (vFileNames[0].c_str())+"_graph.txt";
    string txtFileParams=GetLocation (vFileNames[0].c_str()) +"_parameters.txt";
    Double_t par[5];
    ifstream fin_par(txtFileParams);
    string s;
    while(getline(fin_par, s)){
        stringstream p(s);
        for(int k = 0;k<5;k++){
            p>>par[k];
        }
    }
    rootFileInput+="_all_reconstructed.root";
    rootFileOutput+="_track.root";
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
     // int NumberEvDis = 1000;
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
    int minEn = (int)nentries[0];
    for(int i = 0; i < NumberOfEB; i++){
        if(nentries[i] < minEn && nentries[i]>0){
            minEn = (int)nentries[i];
        }
    }
    cout << "Number of spills " << minEn << endl;

    TFile wfile(rootFileOutput.c_str(), "recreate");
    TDirectory *events2D_dist = wfile.mkdir("events2D_dist");
    TDirectory *time_resolution = wfile.mkdir("time_resolution");
    TDirectory *events2D = wfile.mkdir("events2D");
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
                temp++;
            }
            fmap.close();
        }
    }

    ostringstream sEventnum;
    string sEvent;
    Double_t energyDep[48];
    Double_t energyDepXZ[48];
    Double_t energyDepYZ[48];

    TH2F *Energy_for_each_event[48];
    for (Int_t ih=0; ih < 48;ih++){
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "Energy_each_event"+sEventnum.str();
        Energy_for_each_event[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(),  25,(int)15,(int)100, 25,(int)15,(int)100);  
    }
   
    TH2F *Energy_dist = new TH2F("Energy distribution","Energy distribution",  150,(int)15,(int)200, 150,(int)15,(int)200);  

    TH1F *event_Time_before_Fit;
        sEventnum.str("");
        sEvent = "event_Time_before_fit"+sEventnum.str();
        event_Time_before_Fit = new TH1F("Trigger time : 120 [2.5 ns]",sEvent.c_str(),200,(int)6,(int)10);

    TH1F *event_Time_after_Fit;
        sEventnum.str("");
        sEvent = "event_Time_after_fit"+sEventnum.str();
        event_Time_after_Fit = new TH1F("Trigger time : 120 [2.5 ns]",sEvent.c_str(),200,(int)6,(int)10);

    TH2F *event_XY;
        sEventnum.str("");
        sEvent = "event_XY"+sEventnum.str();
        event_XY = new TH2F(sEvent.c_str(),sEvent.c_str(), 24,(int)0,(int)24, 8,(int)0,(int)8);

  
    TH2F *event_YZ;
        sEventnum.str("");
        sEvent = "event_YZ"+sEventnum.str();
        event_YZ = new TH2F(sEvent.c_str(),sEvent.c_str(), 48,(int)0,(int)48, 8,(int)0,(int)8);
  
    TH2F *event_XZ;
        sEventnum.str("");
        sEvent = "event_XZ"+sEventnum.str();
        event_XZ = new TH2F(sEvent.c_str(),sEvent.c_str(), 24,(int)0,(int)24, 48,(int)0,(int)48);

    TH1F *event_LY;
        sEventnum.str("");
        sEvent = "event_LY"+sEventnum.str();
        event_LY = new TH1F(sEvent.c_str(),sEvent.c_str(),48,(int)0,(int)48);

    TH1F *event_Time;
        sEventnum.str("");
        sEvent = "event_Time"+sEventnum.str();
        event_Time = new TH1F(sEvent.c_str(),sEvent.c_str(),4000,(int)0,(int)4000);
  
    TH1F *event_Time_Fit;
        sEventnum.str("");
        sEvent = "event_Time"+sEventnum.str();
        event_Time_Fit = new TH1F(sEvent.c_str(),sEvent.c_str(),200,(int)0,(int)200);


    TH1F *trigger_Time;
        sEventnum.str("");
        sEvent = "trigger_Time"+sEventnum.str();
        trigger_Time = new TH1F(sEvent.c_str(),sEvent.c_str(),4000,(int)0,(int)4000);

   Int_t eventNum=0;
    bool LargehitTimeDif = 0;
    TCanvas *c1 = new TCanvas("c1","c1", 1480, 1160);
    bool SpillMised = false;
    for (Int_t subSpill = 0; subSpill<minEn; subSpill++) {
        Int_t SpillNumber = subSpill; 
        cout << "Getting Spill Number " << SpillNumber + 1 << endl;
        for (int ik = 0; ik < 19; ik++){
            FEBtree[FEBs[ik]]->GetEntry(SpillNumber);
            if (FEB[FEBs[ik]].SpillTag->back() != SpillNumber + 1)  break;
            if (FEB[FEBs[ik]].SpillTag->size() < 2  ){
                cout << "NULL"<<endl;
                SpillMised = true;
                break;
            } else {
                SpillMised = false;
            }
        }

        if (!SpillMised){

            for ( int TOFtrigger = 0; TOFtrigger < FEB[febTrigger].FEBSN->size(); TOFtrigger++){
                
                if (FEB[febTrigger].hitTimeDif->at(TOFtrigger) > 0/* && NumberEvDis > eventNum  */&& FEB[febTrigger].hitsChannel->at(TOFtrigger) == 1){
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
                                    if (FEB[FEBs[i]].hitTimeDif->at(check) > 50) LargehitTimeDif = 1;
                                    if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000)  event_Time_Fit->Fill(fpeaks((double)FEB[FEBs[i]].hitCharge_pe->at(check),par));
                                    if ( FEBs[i] == 0 || FEBs[i] == 16){
                                        event_XY->Fill((int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],(int)MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check));
                                        event_Time->Fill((int)FEB[FEBs[i]].hitLeadTime->at(check));
                                        if (!triggerDisplay){
                                            trigger_Time->Fill(FEB[febTrigger].hitLeadTime->at(TOFtrigger));
                                            triggerDisplay = true;
                                        }
                                    } else if ( FEBs[i] == 1 || FEBs[i] == 2 || FEBs[i] == 17 || FEBs[i] == 24){
                                        event_YZ->Fill((int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],(int)MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check));
                                        event_Time->Fill((int)FEB[FEBs[i]].hitLeadTime->at(check));
                                
                                        if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000) {
                                            z_y.push_back({(int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],(int)MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check)});
                                            energyDep[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                            energyDepYZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                        }
                                        if (MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] == 0 || MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] == 7) CrossTalk  += FEB[FEBs[i]].hitCharge_pe->at(check);
                                    } else {
                                        event_XZ->Fill((int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],(int)MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check));
                                        event_Time->Fill((int)FEB[FEBs[i]].hitLeadTime->at(check));
                                        if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000){
                                            x_z.push_back({(int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],(int)MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check)});
                                            energyDepXZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                            energyDep[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                        }
                                        if ((int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] == 0 || (int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] == 23) CrossTalk  += FEB[FEBs[i]].hitCharge_pe->at(check);
                                    }
                                }   
                            }
                        }
                    }

                    for (int ik = 0; ik < 40; ik++ ){
                        if (energyDepXZ[ik] > 5 && energyDepXZ[ik+2] > 5 && energyDepXZ[ik+4] > 5 && energyDepXZ[ik+6] > 5 &&
                            energyDepXZ[ik+1] < 5 && energyDepXZ[ik+3] < 5 && energyDepXZ[ik+5] < 5 && energyDepXZ[ik+7] < 5) LargehitTimeDif = 1;

                        if (energyDepYZ[ik] > 5 && energyDepYZ[ik+2] > 5 && energyDepYZ[ik+4] > 5 && energyDepYZ[ik+6] > 5 &&
                            energyDepYZ[ik+1] < 5 && energyDepYZ[ik+3] < 5 && energyDepYZ[ik+5] < 5 && energyDepYZ[ik+7] < 5) LargehitTimeDif = 1;
                    }

                    if ( LargehitTimeDif == 0) {
                        c1->Clear();
                        if (event_XZ->GetEntries()>10 && event_YZ->GetEntries()>10 && CrossTalk < 60 ){
                            Proton res;
                            auto it = find_if(z_y.begin(),z_y.end(), [] (Proton i){return i.par_1 == 0;});
                            res = *it;
                            bool treck = true;
                            for(auto i : z_y){
                                if(abs(i.par_2 - res.par_2) >= 2) treck = false;
                                if((i.par_2 == res.par_2 + 2 || i.par_2 == res.par_2 - 2) && i.p_e > 5 ) treck = false;
                            }
                            it = find_if(x_z.begin(),x_z.end(), [] (Proton i){return i.par_2 == 0;});
                            res = *it;
                            for(auto i : x_z){
                                if(abs(i.par_1 - res.par_1) >= 2) treck = false;
                                if((i.par_1 == res.par_1 + 2 || i.par_1 == res.par_1 - 2) && i.p_e > 5 ) treck = false;
                            }

                            if(treck ){
                                for(int i = 0; i < 48; i++){ 
                                    if(energyDepYZ[i]  > 5 && energyDepXZ[i] > 5){
                                        Energy_for_each_event[i]->Fill(energyDepYZ[i],energyDepXZ[i],1);                       
                                        Energy_dist->Fill(energyDepYZ[i],energyDepXZ[i],1);
                                    }
                                }
                            }
                            if(eventNum< 500 && treck){
                                wfile.cd();
                                events2D->cd();
                                c1->Divide(3,2);
                    
                                c1 -> cd(1);
                                event_XY-> GetYaxis()->SetTitle("Y [cm]");
                                event_XY-> GetXaxis()->SetTitle("X [cm]");
                                event_XY-> Draw("colorz");
        
                                c1 -> cd(2);
                                event_YZ-> GetYaxis()->SetTitle("Y [cm]");
                                event_YZ-> GetXaxis()->SetTitle("Z [cm]");
                                string s = to_string(eventNum);
                                event_YZ-> Draw("colorz");
        
                                c1 -> cd(3);
                                event_XZ-> GetYaxis()->SetTitle("Z [cm]");
                                event_XZ-> GetXaxis()->SetTitle("X [cm]");
                                event_XZ->Draw("colorz");


                                c1 -> cd(4);
                                event_LY-> GetYaxis()->SetTitle("LY [p.e.]");
                                event_LY-> GetXaxis()->SetTitle("Z [cm]");
                                event_LY->Draw("HIST");
        
                                c1 -> cd(5);
                                if(FEB[febTrigger].hitsChannel->at(TOFtrigger) == 0) event_Time->SetTitle("Electrons");
                                if(FEB[febTrigger].hitsChannel->at(TOFtrigger) == 1) event_Time->SetTitle("Muons/Pions");
                                if(FEB[febTrigger].hitsChannel->at(TOFtrigger) == 2) event_Time->SetTitle("Protons");
                    
                                event_Time-> GetYaxis()->SetTitle("N");
                                event_Time-> GetXaxis()->SetTitle("T [2.5 ns]");
                                event_Time->Draw();

                                c1 -> cd(6);
                                trigger_Time->Draw("SAME");

                                c1->Update();
                                c1->Write();
                            }
                            wfile.cd();
                            int binmax = event_Time_Fit->GetMaximumBin();
                            double a = event_Time_Fit->GetXaxis()->GetBinCenter(binmax);                   
                            TF1 * fit_1 = new TF1("fit_1","gaus");
                            event_Time_Fit->Fit("fit_1","","",a-30,a+30);
                            Double_t mean =fit_1->GetParameter("Mean");
                            event_Time_after_Fit->Fill(mean);
                            binmax = event_Time->GetMaximumBin();
                            a = event_Time->GetXaxis()->GetBinCenter(binmax);
                            event_Time->Fit("fit_1","","",a-30,a+30);
                            mean =fit_1->GetParameter("Mean");
                            event_Time_before_Fit->Fill(mean-FEB[febTrigger].hitLeadTime->at(TOFtrigger)+120);

                        }
                    }
                    z_y.clear();
                    x_z.clear();
                    event_Time_Fit->Reset();
                    event_Time->Reset();
                    trigger_Time->Reset();
                    event_XY->Reset();
                    event_YZ->Reset();
                    event_XZ->Reset();
                    event_LY->Reset();

                    eventNum++;
                }
            }
        }
    }
    wfile.cd();
    events2D_dist->cd();
    for(int k = 0; k <48;++k){
        c1->cd();
        Energy_for_each_event[k]->GetYaxis()->SetTitle("XZ[p.e.]");
        Energy_for_each_event[k]->GetXaxis()->SetTitle("ZY[p.e.]");
        Energy_for_each_event[k]->Draw("colorz");
        c1->Write();
        c1->Clear();
        fout <<"x: "<<Energy_for_each_event[k]->GetMean(1)<<" y: "<<Energy_for_each_event[k]->GetMean(2)<<endl;
    }
    Energy_dist->GetYaxis()->SetTitle("XZ[p.e.]");
    Energy_dist->GetXaxis()->SetTitle("ZY[p.e.]");
    Energy_dist->Draw("colorz");
    c1->Write();
    c1->Clear();
    time_resolution->cd();
    c1->cd();
    event_Time_after_Fit-> GetYaxis()->SetTitle("N");
    event_Time_after_Fit-> GetXaxis()->SetTitle("T [2.5 ns]");
    event_Time_after_Fit->Draw();
    c1->Write();
    c1->Clear();
    event_Time_before_Fit-> GetYaxis()->SetTitle("N");
    event_Time_before_Fit-> GetXaxis()->SetTitle("T [2.5 ns]");
    event_Time_before_Fit->Draw();
    c1->Write();
    c1->Clear();
    wfile.Close();
    FileInput->Close();
    return 0;
}
// see results in /..track.root
