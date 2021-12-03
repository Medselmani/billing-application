#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int code;
    int Ht;
    int Qte;
    float Tva;
    char designation[50];
}produit;
typedef struct{
    int Id;
    char nom[50];
    char prenom[50];
    char telephone[50];
    char adresse[50];
}client;
typedef struct{
    int Idclient;
    char nomcliant[50];
    char prenomclient[50];
    char telephoneclient[50];
    int code;
    int totHt;
    float totTva;
    float totTtc;
    int mois;
    int annee;
}facture;
produit nvproduit(int n){
    produit x;
    x.code=n;
    printf("\t\tNom du produit: ");scanf("%s",&x.designation);
    printf("\t\tPrix du produit: ");scanf("%d",&x.Ht);
    printf("\t\tQuantite du stock: ");scanf("%d",&x.Qte);
    printf("\t\tTva: ");scanf("%f",&x.Tva);
    return x;
}
client nvclient(int n){
    client x;
    x.Id=n;
    printf("\t\tNom du client: ");scanf("%s",&x.nom);
    printf("\t\tPrenom: ");scanf("%s",&x.prenom);
    printf("\t\tNulero du telephone: ");scanf("%s",&x.telephone);
    printf("\t\tAdresse du client: ");scanf("%s",&x.adresse);
    return x;
}
//1er fonction: verifier si un produit est existe.
int existe(int code){
    FILE *f;
    produit x;
    char buffer[sizeof(x)];
    int i=0;
    f=fopen("FProduit.txt","r");
    while(fgets(buffer,sizeof(buffer),f)!=0){
        sscanf(buffer,"%d %d %d %f %s",&x.code,&x.Ht,&x.Qte,&x.Tva,x.designation);
        if(code==x.code){
            i=1;
            break;
        }
    }
    fclose(f);
    return i;
}
//2eme fonction: verification si la quantite ne deappase pas la quantite
int depasse(int code,int Qte){
    FILE *f;
    produit x;
    char buffer[sizeof(x)];
    int i=0;
    f=fopen("FProduit.txt","r");
    while(fgets(buffer,sizeof(buffer),f)!=0){
        sscanf(buffer,"%d %d %d %f %s",&x.code,&x.Ht,&x.Qte,&x.Tva,x.designation);
        if(code==x.code){
            if(Qte<=x.Qte) i=1;
            break;
        }
    }
    fclose(f);
    return i;
}
//3eme fonction: destocker notre stock
int destock(int code){
    FILE *f,*fnv;
    produit x;
    char buffer[sizeof(x)];
    int i=0;
    f=fopen("FProduit.txt","r");
    fnv=fopen("tf.txt","w");
    while(fgets(buffer,sizeof(buffer),f)!=0){
        sscanf(buffer,"%d %d %d %f %s",&x.code,&x.Ht,&x.Qte,&x.Tva,x.designation);
        if(code==x.code){
            x.Qte=0;
            i=1;
        }
        fprintf(fnv,"%d %d %d %f %s\n",x.code,x.Ht,x.Qte,x.Tva,x.designation);
    }
    fclose(f);
    fclose(fnv);

    if(i==1){
        remove("FProduit.txt");
        rename("tf.txt","FProduit.txt");
    }else remove("tf.txt");
    return i;
}
//4eme fonction: afficher la liste des factures
int listefactures(int code){
    FILE *f;
    facture x;
    char buffer[sizeof(x)];
    int i=0;

    f=fopen("FFacture.txt","r");
    while(fgets(buffer,sizeof(buffer),f)!=0){
        sscanf(buffer,"%d %s %s %s %d %d %f %f",&x.Idclient,x.nomcliant,x.prenomclient,x.telephoneclient,&x.code,&x.totHt,&x.totTtc,&x.totTva);
        if(code==x.Idclient){
            i++;
            printf("%d\t",i);
            printf("Facture %d: %d\t%s\t%s\t%s\n%d\t%f\t%f\n",x.code,x.Idclient,x.nomcliant,x.prenomclient,x.telephoneclient,x.totHt,x.totTtc,x.totTva);
            
        }
    }
    fclose(f);
    return i;
}
//5eme fonction: ajouter un client au fichier 
void ajouterclient(client x){
    FILE *f;
    f=fopen("FClient.txt","a");
    fprintf(f,"%d %s %s %s %s\n",x.Id,x.nom,x.prenom,x.telephone,x.adresse);
    fclose(f);
}
//6eme fonction: supprimer un client du fichier
int supprimerclient(int code){
    FILE *f,*ft;
    client x;
    char buffer[sizeof(x)];
    int i=0;

    f=fopen("FClient.txt","r");
    ft=fopen("ft.txt","w");
    while(fgets(buffer,sizeof(buffer),f)!=0){
        sscanf(buffer,"%d %s %s %s %s",&x.Id,x.nom,x.prenom,x.telephone,x.adresse);
        if(code==x.Id){
            i=1;
        }else fprintf(ft,"%d %s %s %s %s\n",x.Id,x.nom,x.prenom,x.telephone,x.adresse);
    }

    fclose(f);
    fclose(ft);
    if(i==1){
        remove("FClient.txt");
        rename("ft.txt","FClient.txt");
    }else remove("ft.txt");
    return i;
}
//7eme fonction: afficher la liste des clients
void afficherlalisteclient(){
    FILE *f;
    client x;
    char buffer[sizeof(x)];

    f=fopen("FClient.txt","r");
    while(fgets(buffer,sizeof(buffer),f)!=0){
        sscanf(buffer,"%d %s %s %s %s",&x.Id,x.nom,x.prenom,x.telephone,x.adresse);
        printf("Client: %d\n %s %s-%s %s\n",x.Id,x.nom,x.prenom,x.telephone,x.adresse);
    }
    fclose(f);
}
//8eme fonction: ajouter un produit au fichier
void ajouterproduit(produit x){
    FILE *f;
    f=fopen("FProduit.txt","a");
    fprintf(f,"%d %d %d %f %s\n",x.code,x.Ht,x.Qte,x.Tva,x.designation);
    fclose(f);
}
//9eme fonction: supprimer un produit
int supprimerproduit(int code){
    FILE *f,*ft;
    produit x;
    char buffer[sizeof(x)];
    int i=0;

    f=fopen("FProduit.txt","r");
    ft=fopen("ft.txt","w");
    while(fgets(buffer,sizeof(buffer),f)!=0){
        sscanf(buffer,"%d %d %d %f %s",&x.code,&x.Ht,&x.Qte,&x.Tva,x.designation);
        if(code==x.code){
            i=1;
        }else fprintf(ft,"%d %d %d %f %s\n",x.code,x.Ht,x.Qte,x.Tva,x.designation);
    }

    fclose(f);
    fclose(ft);
    if(i==1){
        remove("FProduit.txt");
        rename("ft.txt","FProduit.txt");
    }else remove("ft.txt");
    return i;
}
//10eme fonction: afficher la liste des produit
void afficherlalisteproduit(){
    FILE *f;
    produit x;
    char buffer[sizeof(x)];

    f=fopen("FProduit.txt","r");
    while(fgets(buffer,sizeof(buffer),f)!=0){
        sscanf(buffer,"%d %d %d %f %s",&x.code,&x.Ht,&x.Qte,&x.Tva,x.designation);
        printf("Produit: %s\n%d %d %d %f \n",x.designation,x.code,x.Ht,x.Qte,x.Tva);
    }
    fclose(f);
}
//11eme fonction: etablir un facture
void etablirfacture(int codeclient,int codeproduit,int qte,int n){
    FILE *f1,*f2,*f3,*t1;
    produit x1;
    client x2;
    facture x3;
    int b1=0,b2=0,b3=0;
    char buffer1[sizeof(x1)],buffer2[sizeof(x2)];

    f1=fopen("FProduit.txt","r");
    t1=fopen("FProduitT.txt","w");
    while(fgets(buffer1,sizeof(buffer1),f1)){
        sscanf(buffer1,"%d %d %d %f %s",&x1.code,&x1.Ht,&x1.Qte,&x1.Tva,x1.designation);
        if(x1.code==codeproduit){
            b1=1;
            f2=fopen("FClient.txt","r");
            while(fgets(buffer2,sizeof(buffer2),f2)!=0){
                sscanf(buffer2,"%d %s %s %s %s",&x2.Id,x2.nom,x2.prenom,x2.telephone,x2.adresse);
                if(x2.Id==codeclient){
                    b2=1;
                    if(qte<=x1.Qte){
                        b3=1;
                        x3.code=n;
                        x3.Idclient=x2.Id;
                        strcpy(x3.nomcliant,x2.nom);
                        strcpy(x3.prenomclient,x2.prenom);
                        strcpy(x3.telephoneclient,x2.telephone);
                        x3.totHt=x1.Ht*qte;
                        x3.totTtc=x3.totHt*(x1.Tva/100);
                        x3.totTva=x3.totTtc+x3.totHt;
                        printf("Mois: ");scanf("%d",&x3.mois);
                        printf("Annee: ");scanf("%d",&x3.annee);
                        f3=fopen("FFacture.txt","a");
                        fprintf(f3,"%d %s %s %s %d %d %f %f %d %d\n",x3.Idclient,x3.nomcliant,x3.prenomclient,x3.telephoneclient,x3.code,x3.totHt,x3.totTtc,x3.totTva,x3.mois,x3.annee);
                        fclose(f3);
                        x1.Qte=x1.Qte-qte;
                    }
                    break;
                }
            }
            fclose(f2);
        }
        fprintf(t1,"%d %d %d %f %s\n",x1.code,x1.Ht,x1.Qte,x1.Tva,x1.designation);
    }
    fclose(f1);
    fclose(t1);

    if(b1==0){
        printf("Produit n'existe pas\n");
        remove("FProduitT.txt");
    }else{
        if(b2==0){
            printf("Client n'existe pas\n");
            remove("FProduitT.txt");
        }else{
            if(b3==0){
                printf("Quantite %d indisponible\n",qte);
                remove("FProduitT.txt");
            }else{
                printf("Facture etablir avec succes\n");
                remove("FProduit.txt");
                rename("FProduitT.txt","FProduit.txt");
            }
        }
    }
}
//12eme fonction: afficher la liste des facture
void afficherlistefacture(){
    FILE *f;
    facture x3;
    char buffer[sizeof(x3)];
    
    f=fopen("FFacture.txt","r");
    while(fgets(buffer,sizeof(buffer),f)!=0){
        sscanf(buffer,"%d %s %s %s %d %d %f %f %d %d",&x3.Idclient,x3.nomcliant,x3.prenomclient,x3.telephoneclient,&x3.code,&x3.totHt,&x3.totTtc,&x3.totTva,&x3.mois,&x3.annee);
        printf("Facture %d: %d\t%s\t%s\t%s\n%d\t%f\t%f\t%d\t%d\n",x3.code,x3.Idclient,x3.nomcliant,x3.prenomclient,x3.telephoneclient,x3.totHt,x3.totTtc,x3.totTva,x3.mois,x3.annee);
    }
    fclose(f);
}
//13eme fonction: afficher la liste 
void afficherlistefactureperiode(int mois,int annee){
    FILE *f;
    facture x3;
    char buffer[sizeof(x3)];
    
    f=fopen("FFacture.txt","r");
    while(fgets(buffer,sizeof(buffer),f)!=0){
        sscanf(buffer,"%d %s %s %s %d %d %f %f %d %d",&x3.Idclient,x3.nomcliant,x3.prenomclient,x3.telephoneclient,&x3.code,&x3.totHt,&x3.totTtc,&x3.totTva,&x3.mois,&x3.annee);
        if(x3.annee==annee && x3.mois==mois){
            printf("Facture %d: %d\t%s\t%s\t%s\n%d\t%f\t%f\t%d\t%d\n",x3.code,x3.Idclient,x3.nomcliant,x3.prenomclient,x3.telephoneclient,x3.totHt,x3.totTtc,x3.totTva,x3.mois,x3.annee);
        }
    }
    fclose(f);
}
void menu(){
    printf("\n\n\n     ********************************************************************\n");
    printf("         Menu                                                       \n");
    printf("\n");
    printf("            1-Afficher la liste des clients\n");
    printf("            2-Afficher la liste des produit\n");
    printf("            3-Afficher la liste des factures\n");
    printf("            4-Ajouter un client\n");
    printf("            5-Ajouter un produit\n");
    printf("            6-Etablir un facture\n");
    printf("            7-Afficher la liste des facture d'un client\n");
    printf("            8-Verifier si un produit est disponible ou non\n");
    printf("            9-Destocker\n");
    printf("            10-Supprimer un client\n");
    printf("            11-Supprimer un produit\n");
    printf("            12-Afficher les factures d'une periode\n");
    printf("        0-sortir\n");
    printf("     ********************************************************************\n\n\n");
}
void main(){
    int i;
    int nc=0,np=0,nf=0;
    int c1,c2,q;
    do{
        menu();
        scanf("%d",&i);
        switch(i){
            case 1:{
                afficherlalisteclient();
                break;
            }
            case 2:{
                afficherlalisteproduit();
                break;
            }
            case 3:{
                afficherlistefacture();
                break;
            }
            case 4:{
                nc++;
                ajouterclient(nvclient(nc));
                break;
            }
            case 5:{
                np++;
                ajouterproduit(nvproduit(np));
                break;
            }
            case 6:{
                printf("Donnez moi le code du produit et client aprs la quantite: ");
                scanf("%d %d %d",&c1,&c2,&q);
                nf++;
                etablirfacture(c2,c1,q,nf);
                break;
            }
            case 7:{
                printf("code du client: ");scanf("%d",&c1);
                if(listefactures(c1)==0) printf("Client n'existe pas ou n'a pas des factures\n");
                break;
            }
            case 8:{
                printf("donnez moi le code du produit: ");scanf("%d",&c1);
                if(existe(c1)==1) printf("produit existe\n"); else printf("produit n'existe pas\n");
                break;
            }
            case 9:{
                printf("donnez moi le code du produit: ");
                scanf("%d",&c1);
                if(destock(c1)==0) printf("produit n'existe pas\n"); else printf("stock destocker\n");
                break;
            }
            case 10:{
                printf("donnez moi le code du client: ");
                scanf("%d",&c1);
                if(supprimerclient(c1)==0) printf("client indisponible\n"); else{
                    printf("client supprimer\n");
                    nc--;
                }
                break;
            }
            case 11:{
                printf("donnez moi le code du produit: ");
                scanf("%d",&c1);
                if(supprimerproduit(c1)==0) printf("produit indisponible\n"); else{
                    printf("produit supprimer\n");
                    np--;
                }
                break;
            }
            case 12:{
                printf("donnez moi le moi et l'annee: ");
                scanf("%d %d",&c1,&c2);
                afficherlistefactureperiode(c1,c2);
                break;
            }
        }
    }while(i!=0);
}
