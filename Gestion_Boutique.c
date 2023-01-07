#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>

#define MAX_STOCK 1000
#define MAX_NOM_PRODUIT 20

//convertiseur de couleur
void convertisseur(int couleurDuText,int couleurDefond)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDefond*16+couleurDuText);
}
//collecting color from the code
void couleur(char mot[]){
	if(strcmp(mot, "bleu")==0){
    	convertisseur(9,0);
	}else if(strcmp(mot, "rouge")==0){
    	convertisseur(12, 0);
	}else if(strcmp(mot, "violet")==0){
    	convertisseur(5, 0);
	}else if(strcmp(mot, "jaune")==0){
    	convertisseur(6, 0);
	}else if(strcmp(mot, "vert")==0){
    	convertisseur(2, 0);
	}
}
typedef struct Number{
        int nombre_vendeur;
        int nombre_produit;
        int nombre_vendu;
        int nombre_admin;
        int nombre_acheteur;
} Number;

Number* creeNumber(){
    Number* number=(Number*)malloc(sizeof(Number));
     number->nombre_admin=0;
    number->nombre_produit=0;
    number->nombre_vendu=0;
    number->nombre_vendeur=0;
    number->nombre_acheteur=0;
    return number;
    
}
typedef struct Produit{
    char nom_produit[MAX_NOM_PRODUIT];
    int quantite;
    int prix_unite;
    int range;
    int niveau;
} Produit;

Produit* creeProduit(){
    Produit* produit=(Produit*)malloc(sizeof(Produit));

    return produit;
}

typedef struct Vendeur{
    char nom_vendeur[MAX_NOM_PRODUIT];
    int numero;
} Vendeur;

Vendeur* creeVendeur(){
    Vendeur* vendeur=(Vendeur*)malloc(sizeof(Vendeur));
    return vendeur;
}

typedef struct Admin{
    char nom[MAX_NOM_PRODUIT];
    char password_system[MAX_NOM_PRODUIT];
    char password_admin[MAX_NOM_PRODUIT];
} Admin;

Admin* creeAdmin(){
    Admin* admin=(Admin*)malloc(sizeof(Admin));
}

typedef struct Acheteur{
        char nom[MAX_NOM_PRODUIT];
        int nombre_visite;
} Acheteur;

int creeAcheteur( char nom[], Acheteur liste_acheteur[], int nombre_acheteur){
        Acheteur* acheteur=(Acheteur*)malloc(sizeof(Acheteur));
        strcpy(acheteur->nom, nom);
        ++acheteur->nombre_visite;
        liste_acheteur[nombre_acheteur]=*acheteur;
        ++nombre_acheteur;
        return nombre_acheteur;
}


void write_acheteur_file(FILE *acheteur, Acheteur liste_acheteur[]){
            acheteur=fopen("acheteur.data", "w");
            fwrite(liste_acheteur, MAX_STOCK*sizeof(Acheteur), 1, acheteur);
            fclose(acheteur);
}
void read_acheteur_file(FILE *acheteur, Acheteur liste_acheteur[]){
            acheteur=fopen("acheteur.data", "r");
            fread(liste_acheteur, MAX_STOCK*sizeof(Acheteur), 1, acheteur);
            fclose(acheteur);
}

int ajout_stock(Produit* produit, Produit liste_produit[], int nombre_produit){
        int vue=0;
        int i;
        for(i=0; i<MAX_STOCK; i++){
            if(strcmp(liste_produit[i].nom_produit, produit->nom_produit)==0){
                liste_produit[i].quantite=produit->quantite+liste_produit[i].quantite;
                return nombre_produit;
            }
        }
        liste_produit[nombre_produit]=*produit;
        ++nombre_produit;
        return nombre_produit;
}

void write_stock_file(FILE *stock, Produit liste_produit[]){
            stock=fopen("stock.data", "w");
            fwrite(liste_produit, MAX_STOCK*sizeof(Produit), 1, stock);
            fclose(stock);
}

void read_stock_file(FILE *stock, Produit liste_produit[]){
            stock=fopen("stock.data", "r");
            fread(liste_produit, MAX_STOCK*sizeof(Produit), 1, stock);
            fclose(stock);
}

int ajout_vendeur(Vendeur* vendeur, Vendeur liste_vendeur[], int nombre_vendeur){
         liste_vendeur[nombre_vendeur]=*vendeur;
         ++nombre_vendeur;
         return nombre_vendeur;
} 

void write_vendeur_file(FILE *vendeur, Vendeur liste_vendeur[]){
            vendeur=fopen("vendeur.data", "w");
            fwrite(liste_vendeur, MAX_NOM_PRODUIT*sizeof(Vendeur), 1, vendeur);
            fclose(vendeur);
}
void write_number_file(FILE *numbers, Number* num){
            numbers=fopen("numbers.data", "w");
            fwrite(num, sizeof(Number), 1, numbers);
            fclose(numbers);
}
void read_number_file(FILE *numbers, Number* num){
            numbers=fopen("numbers.data", "r");
            fread(num, sizeof(Number), 1, numbers);
            fclose(numbers);
}

void read_vendeur_file(FILE *vendeur, Vendeur liste_vendeur[]){
            vendeur=fopen("vendeur.data", "r");
            fread(liste_vendeur, MAX_NOM_PRODUIT*sizeof(Vendeur), 1, vendeur);
            fclose(vendeur);
}


void write_admin_file(FILE *admin, Admin* adminis){
            admin=fopen("admin.data", "w");
            fwrite(adminis, sizeof(Admin), 1, admin);
            fclose(admin);
}

void read_admin_file(FILE *admin, Admin* adminis){
            admin=fopen("admin.data", "r");
            fread(adminis, sizeof(Admin), 1, admin);
            fclose(admin);
}

void write_bilan_file(FILE *bilan, Produit liste_vendu[]){
            bilan=fopen("bilan.data", "w");
            fwrite(liste_vendu, 2*MAX_STOCK*sizeof(Produit), 1, bilan);
            fclose(bilan);
}
void read_bilan_file(FILE *bilan, Produit liste_vendu[]){
            bilan=fopen("bilan.data", "r");
            fread(liste_vendu, 2*MAX_STOCK*sizeof(Produit), 1, bilan);
            fclose(bilan);
}



Produit* panier(){
    int i=0, ajouter=1;
    char nom[MAX_NOM_PRODUIT];
    int a;
    int quantite=0;
    Produit *_panier;
        couleur("jaune");
            printf("--------Voici le panier. veuiller entrer les produit.-------\n\n\n");
            couleur("rouge");
            printf("N/B Ajouter les produit suivie de leur quantiter ligne par ligne\n");
            printf("Pour stoper la boucle, taper 0\n");
    do{
            printf("Nom : ");
            scanf("%s", &_panier[i].nom_produit);
            printf("Quantiter : ");
            scanf("%d",&_panier[i].quantite );
            ++i;
            printf("Ya til plus de produit? Taper 1 pour ajouter au panier : ");
            scanf("%d", &a);
            ajouter=a;
            
    }while(ajouter==1);
    return _panier;
}

int vendre_produit( Produit panier[],int nombre, Produit liste_produit[], Produit liste_vendu[], Vendeur* vendeur, Acheteur liste_acheteur[], int nombre_acheteur ){
            int i,j;
            int vue=0;
            int Prix_total=0;
            int a;
            int p;
            for(j=0; j<MAX_NOM_PRODUIT; j++){
            for(i=0; i<MAX_STOCK; i++){
                if(strcmp(liste_produit[i].nom_produit, panier[j].nom_produit)==0){
                    if(liste_produit[i].quantite<panier[j].quantite){
                        printf("Pas assez de %s en stock\n", liste_produit[i].nom_produit);
                    }
                    couleur("bleu");
                    printf("Le prix total de %s sera de : %d\n", liste_produit[i].nom_produit, p=panier[j].quantite*liste_produit[i].prix_unite );
                    if(p==0)
                    	break;
                    liste_produit[i].quantite=liste_produit[i].quantite - panier[j].quantite;
                    liste_vendu[nombre]=panier[j];
                    
                    Prix_total=Prix_total+p;
                    ++nombre;
                    vue=1;
                    
                }
            }
            if(p==0)
            	break;
          }  if(!vue){
                printf("produit non trouver");
            }
            char nom_acheteur[MAX_NOM_PRODUIT];
            couleur("rouge");
            printf("-----Gestionaire de Compte Acheteur-----\n\n");
            couleur("vert");
            printf("Entrer le nom de l'acheteur : ");
            scanf("%s",&nom_acheteur);
            int vued=0;
            for(i=0; i<MAX_STOCK; i++){
                if(strcmp(nom_acheteur, liste_acheteur[i].nom)==0){
                    if(liste_acheteur[i].nombre_visite>4){
                    	a=i;
                    	printf("\n BONUS");
                        printf("\n\n\n");
                        couleur("rouge");
                        printf("BRAVO VOUS NOUS AVEZ VISITEZ PLUS DE 4 FOIS ALORS VOUS RECEVEZ UNE REMISE DE 3 pourcent\n\n");
                        couleur("bleu");
                        printf("---------------Facture---------------------\n\n");
                        printf("Nom      ||  Quantite  ||  PU   ||  PT\n");
                         vued=0;
                   
                   for(j=0; j<MAX_NOM_PRODUIT; j++){
                        for(i=0; i<MAX_STOCK; i++){
                            
                                vued=1;
                                if(strcmp(liste_produit[i].nom_produit,panier[j].nom_produit)==0){
                                printf("--------------------------------------------\n");
                                 printf("%s || %d  ||   %d   ||  %d   \n", panier[j].nom_produit, panier[j].quantite, liste_produit[i].prix_unite, panier[j].quantite*liste_produit[i].prix_unite );
                        
                            }}
                            if(liste_produit[i].prix_unite==0)
                            		break;
                           if(vued)
						   		break;
                        }
                        printf("------------\n");
                        printf("------Prix Total = %d", Prix_total);
                        printf("------Bonus reduction de 3pourcent\n");
                        couleur("rouge");
                        printf("Prix a payer : %f", (Prix_total*0.97));
                        liste_acheteur[a].nombre_visite=0;
                        
                        return nombre;
                    }
                    else{
                    	printf("\n VUED");
                        printf("\n\n\n");
                       
                        couleur("bleu");
                        printf("---------------Facture---------------------\n\n");
                        printf("Nom      ||  Quantite  ||  PU   ||  PT\n");
                        vued=0;
                  for(j=0; j<MAX_NOM_PRODUIT; j++){
                        for(i=0; i<MAX_STOCK; i++){
                            	a=i;
                                vued=1;
                                if(strcmp(liste_produit[i].nom_produit,panier[j].nom_produit)==0){
                                printf("--------------------------------------------\n");
                                 printf("%s || %d  ||   %d   ||  %d   \n", panier[j].nom_produit, panier[j].quantite, liste_produit[i].prix_unite, panier[j].quantite*liste_produit[i].prix_unite );
							if(liste_produit[i].prix_unite==0)
                            		break;
							}
                            }
                            if(vued)
                            if(liste_produit[i].prix_unite==0)
                            		break;
                        
                        }
                        printf("------------\n");
                        printf("------Prix Total = %d", Prix_total);
                        liste_acheteur[a].nombre_visite++;
                        
                    }
                }
            }
            if(!vued){
                nombre_acheteur=creeAcheteur(nom_acheteur, liste_acheteur, nombre_acheteur);
                             printf("\n\n\n");
                       
                        couleur("bleu");
                        printf("---------------Facture---------------------\n\n");
                        printf("Nom      ||  Quantite  ||  PU   ||  PT\n");
                        vued=0;
                        for(j=0; j<MAX_NOM_PRODUIT; j++){
                        for(i=0; i<MAX_STOCK; i++){
                                vued=1;
                                if(strcmp(liste_produit[i].nom_produit,panier[j].nom_produit)==0){
                                printf("--------------------------------------------\n");
                                 printf("%s || %d  ||   %d   ||  %d   \n", panier[j].nom_produit, panier[j].quantite, liste_produit[i].prix_unite, panier[j].quantite*liste_produit[i].prix_unite );
                            }
                            }
                           if(vued)
                                break;
                        }
                        printf("------------\n");
                        printf("------Prix Total = %d", Prix_total);
                        liste_acheteur[nombre_acheteur].nombre_visite++;
                 
            }
            return nombre;
}

Produit* queryProduit(Produit *produit, int n){
    char nom[MAX_NOM_PRODUIT];
    int quant;
    int pu;
    int ranger;
    int niveau;
    printf("--------Ajout de stock-----------\n\n");
    printf("Renseignez les produit a ajouter!\n");
    printf("Produit numero %d \n", n);
    printf("Nom : ");
    scanf("%s", &nom);
     printf("\nQuantite : ");
    scanf("%d", &quant);
     printf("\nPrix Unitaire : ");
    scanf("%d", &pu);
      printf("\nRanger numero : ");
    scanf("%d", &ranger);
      printf("\nEtage numero : ");
    scanf("%d", &niveau);

    produit->niveau=niveau;
    produit->prix_unite=pu;
    produit->quantite=quant;
    produit->range=ranger;
    strcpy(produit->nom_produit, nom);
    return produit;
}

Admin* queryAdmin(Admin* admin){
        char nom[MAX_NOM_PRODUIT];
       char passys[MAX_NOM_PRODUIT];
       char passad[MAX_NOM_PRODUIT];
        printf("Entrer les donner du nouvel admin\n");
        printf("Nom : ");
         scanf("%s", &nom);
        printf("\nMot de passe system : ");
         scanf("%s", &passys);
        printf("\nNom de passe administrateur : ");
         scanf("%s", &passad);
         strcpy(admin->nom, nom);
         strcpy(admin->password_admin, passad);
         strcpy(admin->password_system, passys);
         return admin;

        
}
void listeVendeur(Vendeur liste_vendeur[], int nombre){
	int i;
	for(i=0; i<nombre; i++){
		printf("%d-->%s\n", liste_vendeur[i].numero, liste_vendeur[i].nom_vendeur);
		
	}
}

Vendeur* queryVendeur(Vendeur* vendeur, int numero){
     char nom[MAX_NOM_PRODUIT];
     printf("\nNom : ");
     scanf("%s", &nom);
     strcpy(vendeur->nom_vendeur, nom);
     vendeur->numero=numero;
     return vendeur;
}

void afficheListeProduit(Produit liste_produit[]){
    int i;
    printf("--------------STOCK ACTUEL-----------------\n");
    for(i=0; i<MAX_STOCK; i++){
        printf("-------------------------------------\n");
        printf("------------Nom : %s ----------------\n", liste_produit[i].nom_produit);
        printf("------------Quantiter : %d---------\n", liste_produit[i].quantite);
        printf("------------PRIX UNITAIRE : %d ------------\n", liste_produit[i].prix_unite);
        printf("------------Ranger numero : %d------------\n", liste_produit[i].range);
        printf("------------Etage : %d\n", liste_produit[i].niveau);
        if(liste_produit[i].niveau==0 || liste_produit[i].niveau>100 ){
                break;
        }
        
    }
}

void rechercheProduit(Produit liste_produit[]){
    char nom[MAX_NOM_PRODUIT];
    int i;
    printf("--------Service de recherche dans le stock------------\n\n");
    printf("Nom du produit a chercher! : ");
    scanf("%s", nom);
    int seen=0;
    for(i=0; i<MAX_STOCK; i++){
        if(strcmp(nom, liste_produit[i].nom_produit)==0){
        printf("--------PRODUIT TROUVER------------");
        printf("Nom : %s\n", liste_produit[i].nom_produit);
        printf("Quantiter : %d\n", liste_produit[i].quantite);
        printf("PRIX UNITAIRE : %d\n", liste_produit[i].prix_unite);
        printf("Ranger numero : %d\n", liste_produit[i].range);
        printf("Etage : %d\n", liste_produit[i].niveau);
        seen=1;
        }
    }
    if(!seen)
        printf("Produit inexistant! veuiller verifier si le nom entrer est correct");
}
void alert(Produit liste_produit[]){
    int i;
    
    for(i=0; i<MAX_STOCK; i++){
        if(liste_produit[i].quantite<=10 && liste_produit[i].niveau<1&& liste_produit[i].niveau>20){
            couleur("rouge");
            printf("ALERT ALERT ALERT!\n");
            printf("Le produit %s est presque fini en stock veuiller le recharger il reste %d exemplaire\n", liste_produit[i].nom_produit, liste_produit[i].quantite);
    }
    }
}

void bilanVendeur(Produit liste_vendu[], int numero){
        int i, p;
        int Prix=0;
        printf("Votre bilan depui toujour! \n");
    
        for(i=0; i<MAX_STOCK; i++){
            printf("-------------------------------");
            printf("%s \n", liste_vendu[i].nom_produit);
            printf("Qantite : %d   ||     Prix Total : %d \n", liste_vendu[i].quantite );
          
            if(liste_vendu[i].quantite==0 || liste_vendu[i].quantite>1000){
                break;
            }
        }
    
}

void bilanAdmin(Produit liste_vendu[]){
        int i, j, p, Prix;
        int error=0;
        
            
            for(j=0; j<2*MAX_STOCK; j++){
            printf("-------------------------------");
            printf("%s \n", liste_vendu[j].nom_produit);
            printf("Qantite : %d   || \n", liste_vendu[j].quantite);

            }

       
}

int adminMenu(){
    sleep(2);
    printf("********Welcome Administrator*********\n\n");
    sleep(2);
    int reponse;
    couleur("jaune");
    printf("------------Que Voulez vous Faire-------? \n\n");
    printf("1:)  Voir le Bilan des Vente\n\n");
    printf("2:)  Ajouter Un Vendeur\n\n");
    printf("3:)  Changer de mot de pass system pour les Vendeur\n\n");
    printf("4:)  Changer Vos Donner  Administrateur\n\n");
    printf("5:)  Augmenter le Stock\n\n");
    printf("6:)  Voir tout les produit\n\n");
    printf("7:)  Voir la liste des vendeur\n\n");
    printf("8:)  Deconnecter\n\n");
    
    printf("Veuillez Entrer votre reponse ici -->  ");
    scanf("%d", &reponse);
    return reponse;
}
int adminInterface(FILE* numb,Number* num, Produit liste_vendu[],Vendeur* vendeur, Vendeur liste_vendeur[], FILE* vend, Admin* admin, FILE* adminis, Produit* produit, FILE* prod, Produit liste_produit[]){
    alert(liste_produit);
    int menuChoice;
    char mot[MAX_NOM_PRODUIT];
    int continuer=0;
    int n;
    menuChoice=adminMenu();
    switch (menuChoice)
    {
    case 1:
        bilanAdmin(liste_vendu);
        break;
    case 2:
        vendeur=queryVendeur(vendeur, num->nombre_vendeur);
        num->nombre_vendeur=ajout_vendeur(vendeur, liste_vendeur, num->nombre_vendeur );
        write_number_file(numb, num);
        write_vendeur_file(vend, liste_vendeur);
        break;
    case 3:
        couleur("jaune");
        printf("Entrer le nouveau mot de passe system : ");
        scanf("%s", &mot);
        strcpy(admin->password_system, mot);
        printf("\n----Mot de passe changer avec succes!-----\n");
        break;
    case 4:
        admin=queryAdmin(admin);
        write_admin_file(adminis, admin);
        break;
    case 5:
        
        while(continuer==0){
            produit=queryProduit(produit, num->nombre_produit );
            num->nombre_produit=ajout_stock(produit, liste_produit, num->nombre_produit );
            write_number_file(numb, num);
            write_stock_file(prod, liste_produit);
            printf(" Continuer?\n 0. Oui \n 1. Non \n reponse : ");
            scanf("%d", &continuer);
        }
        printf("Produit ajouter avec success!");
        break;
    case 6:
        afficheListeProduit(liste_produit);
        break;
    case 7:
    	listeVendeur(liste_vendeur, num->nombre_vendeur);
    	break;
    case 8:
        return 2;
        break;
    default:
        printf("Entrer une Valeur valide\n\n");
        adminInterface(numb, num, liste_vendu, vendeur, liste_vendeur, vend, admin, adminis, produit, prod, liste_produit);
        break;
    }
        int state;
        printf("\n\nWhat Next? \n tap 1 to exit app and 0 to return to your main menu : ");
        scanf("%d", &state);
        if(state)
            return 0;
        if(!state)
            adminInterface(numb, num,  liste_vendu, vendeur,liste_vendeur, vend, admin, adminis, produit, prod, liste_produit);
    return 1;
}

int vendeurMenu(){
	sleep(2);
    printf("------------Welcome Vendeur--------------\n");
    int reponse;
    printf("\n----------Que Voulez vous Faire?----------- \n\n");
    printf("1:)  Vendre des Produit\n\n");
    printf("2:)  Rechercher un Produit\n\n");
    printf("3:)  Voir la liste des Produit\n\n");
    printf("4:)  Voir votre bilan Vendeur\n\n");
    printf("5:)  Deconnecter\n\n");
    printf("Veuillez Entrer votre reponse ici -->  ");
    scanf("%d", &reponse);
    return reponse;
}
int vendeurInterface(FILE *numb, Number* num, FILE* achete, FILE* bilan, Produit *liste_vendu,Vendeur* vendeur, Vendeur liste_vendeur[], FILE* vend, Admin* admin, FILE* adminis, Produit* produit, FILE* prod, Produit liste_produit[], Acheteur liste_acheteur[]){
        alert(liste_produit);
        int i;
        Produit *liste_prod;
        int menuChoise;
		menuChoise=vendeurMenu();
        switch (menuChoise)
        {
        case 1:
            liste_prod=panier();
            num->nombre_vendu=vendre_produit(liste_prod, num->nombre_vendu, liste_produit, liste_vendu, vendeur, liste_acheteur, num->nombre_acheteur);
            write_number_file(numb, num);
            write_stock_file(prod, liste_produit);
            write_acheteur_file(achete, liste_acheteur);
            write_bilan_file(bilan, &liste_vendu);
            write_bilan_file(bilan, &liste_vendu);
            write_acheteur_file(achete, liste_acheteur);
            write_stock_file(prod, liste_produit);
            break;
        case 2:
            rechercheProduit(liste_produit);
            break;
        case 3:
            afficheListeProduit(liste_produit);
            break;
        case 4:
            bilanVendeur(liste_vendu, vendeur->numero);
            break;
        case 5:
            return 2;
            break;
        
        default:
            printf("Entrer une valeur qui marche!  ");
            vendeurInterface(numb, num, achete,  bilan, liste_vendu, vendeur,liste_vendeur, vend, admin, adminis,  produit,prod,  liste_produit,  liste_acheteur );
            break;
        }
        int state;
        printf("\n\nWhat Next? \n tap 1 to exit app and 0 to return to your main menu : ");
        scanf("%d", &state);
        if(state)
            return 0;
        if(!state)
             vendeurInterface(numb, num, achete,  bilan, liste_vendu, vendeur,liste_vendeur, vend, admin, adminis,  produit,prod,  liste_produit,  liste_acheteur);
return 1;
}

int mainFrame(){
    Number *num=creeNumber();
    Produit *produit=creeProduit();
    Vendeur *vender=creeVendeur();
    Admin *admin=creeAdmin();
    Produit liste_produit[MAX_STOCK];
    Vendeur liste_vendeur[MAX_NOM_PRODUIT];
    Acheteur liste_acheteur[MAX_NOM_PRODUIT];
    Produit liste_vendu[2*MAX_NOM_PRODUIT];
    FILE *adminis, *acheteur, *bilan, *stock, *vendeur, *numb;
    read_acheteur_file(acheteur, liste_acheteur);
    read_admin_file(adminis, admin);
    read_bilan_file(bilan, liste_vendu);
    read_number_file(numb, num);printf("Yo no error here!");
    read_stock_file(stock, liste_produit);
    read_vendeur_file(vendeur, liste_vendeur);
    Admin *currentAdmin=creeAdmin();
    Vendeur *currentVendeur=creeVendeur(); 
    if(num->nombre_admin==0){
        admin=queryAdmin(admin);
        write_admin_file(adminis, admin);
        printf("%s ", admin->nom);
        printf("Vous venez de cree un administrateur system! \n");
        num->nombre_admin=1;
        write_number_file(numb, num);
    }

    couleur("rouge");
    printf("************************************************************************************************\n");
    printf("**************                     IVANO-TECHS PLATFORMS                       *****************\n");
    printf("*****                              STORE MAN  FOR ALL                                      *****\n");
    printf("**************                       VERSION 1.1.0                             *****************\n");
    printf("************************************************************************************************\n");
    printf("%s' Store Management", admin->nom);
    int logvar;
    int exitvar;
    int connected=0;
    int i;
    couleur("blue");
    printf("\n\n\n");
    printf("How do you wish to login? \n 1. ADMINISTRATOR \n 2. VENDOR \n Enter answer : ");
    scanf("%d", &logvar);
    if(logvar==1){
            while(connected==0){
            currentAdmin=queryAdmin(currentAdmin);
            if(strcmp(currentAdmin->nom, admin->nom)!=0 || strcmp(currentAdmin->password_admin,admin->password_admin)!=0){
                printf("\n\n----Incorect credentials try again----\n\n");
                continue;
            }
            printf("\n\n******Login successfull!!!*******\n\n");
            exitvar=adminInterface(numb, num, liste_vendu, vender,liste_vendeur, vendeur, admin, adminis, produit, stock, liste_produit);
            connected=1;
            if(exitvar==2){
			
            	couleur("vert");
               printf("\n\nDeconnection........\n");
               sleep(3);
               printf("Deconnecter Success!..........\n\n\n");
               
               sleep(2);
               mainFrame();
			   }
            if(exitvar==0)
                return exitvar;
            }
        }
    connected=0;
    int vendnum;
    if(logvar==2){
        while(connected==0){
            printf("Entrer le numero vendeur : ");
            scanf("%d", &vendnum);
            for(i=0; i<MAX_NOM_PRODUIT; i++){
                if(liste_vendeur[i].numero==vendnum){
                    strcpy(currentVendeur->nom_vendeur, liste_vendeur[i].nom_vendeur);
                    currentVendeur[i].numero=vendnum;
                    printf("\n\n---------Connection success! Bienvenu Mr/mdme %s ----------\n\n\n", liste_vendeur[i].nom_vendeur);
                    couleur("violet");
                    exitvar=vendeurInterface(numb, num, acheteur, bilan, liste_vendu, currentVendeur, liste_vendeur, vendeur, admin, adminis, produit, stock, liste_produit, liste_acheteur);
                      connected=1;
                      if(exitvar==2){
                      		couleur("vert");
                 	        printf("\n\nDeconnection........\n");
               				sleep(3);
               				printf("Deconnecter success!..........\n\n\n");
               				sleep(2);
                         	mainFrame();
						 }
                    if(exitvar==0)
             
                    
                            return exitvar;
                }
            }
        }  printf("Vendeur  non Existant!\n");
    }
}



int main(){
    int exited;
    exited=mainFrame();
    if(exited==0){
		printf(" See you next!");
	    return 0;}
}







