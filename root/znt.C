#include <iostream>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TF1.h>
#include <iomanip>
#include <cmath>

using namespace std;

void znt(){

const int nmisure=8;
double Imin[]={2.60,4.91,5.82,6.83,7.20,7.90,8.90,9.91};
double Imax[]={2.62,4.93,5.85,6.83,7.25,7.93,8.92,9.93};


double ar[]={0.0672,0.00015};
double br[]={0.0074,0.0009};
double ap[]={-0.00452101,5.085e-05};
double bp[]={0.129709,0.000884};
double cp[]={-0.200692,0.004895};
double Im[nmisure];
double sIm[nmisure];
double B[nmisure];
double sB[nmisure];
double dDm[]={0.061,0.125,0.158,0.188,0.198,0.221,0.233,0.263};
double sdDm[]={0.004,0.007,0.003,0.006,0.006,0.004,0.006,0.009};


for(int i = 0;i<nmisure;i++){

Im[i]=(Imax[i]+Imin[i])/2.;

if((Imax[i]-Imin[i])/2. < 0.02)
sIm[i]=0.02;
else{
sIm[i]=(Imax[i]-Imin[i])/2.;
}

if(Im[i]<=7){
B[i]=ar[0]*Im[i]+br[0];
sB[i]=sqrt(pow(Im[i]*ar[1],2)+pow(sIm[i]*ar[0],2)+pow(br[1],2));

if(sB[i]< 0.1035087719*B[i])
sB[i]=0.1035087719*B[i];

cout<<"Im = ("<<Im[i]<<"+-"<<sIm[i]<<") A "<<" -------- "<<"B[Im] = ("<<B[i]<<"+-"<<sB[i]<<") T "<<endl;
}
else{
B[i]=ap[0]*pow(Im[i],2)+bp[0]*Im[i]+cp[0];
sB[i]=sqrt(pow(pow(Im[i],2)*ap[1],2)+pow(((2*Im[i]*ap[0])+bp[0])*sIm[i],2)+pow(Im[i]*bp[1],2)+pow(cp[1],2));

if(sB[i]< 0.1035087719*B[i])
sB[i]=0.1035087719*B[i];

cout<<"Im = ("<<Im[i]<<"+-"<<sIm[i]<<") A "<<" -------- "<<"B[Im] = ("<<B[i]<<"+-"<<sB[i]<<") T "<<endl;
}

}


TCanvas *canvas = new TCanvas("canvas","dDm(B)",0,0,600,400);
canvas->SetFillColor(0);
canvas->cd();

TGraphErrors *TGE = new TGraphErrors(nmisure,B,dDm,sB,sdDm);
TGE->SetMarkerSize(0.6);
TGE->SetMarkerStyle(21);
TGE->SetTitle("d/D(B)");
TGE->GetXaxis()->SetTitle("B [T]");
TGE->GetYaxis()->SetTitle("d/D");
TGE->Draw("AP");

TF1 *func = new TF1("func","[0]*x + [1]",0,6.93);
func->SetParameter(0,0.06);
func->SetParameter(1,0);
func->SetLineColor(2);
func->Draw("same");
TGE->Fit("func","RM+S");

cout << "Chi^2:" << func->GetChisquare() << ", number of DoF: " << func->GetNDF() << " (Probability: " << func->GetProb() << ")." << endl;
cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

