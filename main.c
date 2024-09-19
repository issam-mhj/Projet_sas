#include <stdio.h>


void menu_user();
void stats_rapp();
void sign_up();
void sign_in();

int countclients=0;

struct clients{
    char nom[20]; 
    char prenom[20];
    char identifiant[20];
    char tele[10];
    char mot_de_passe[30];
};

struct clients data[100];



void menu(){
    int choix;
    printf("voulez-vous : \n");
    do{
    printf("(1) Gestion des reclamations\n");
    printf("(2) Statistiques et Rapports\n");
    printf("(3) quitter le programme\n");
    scanf("%d",&choix);
    switch (choix){
        case 1:
           // gestion_recl();
            break;
        case 2:
           // stats_rapp();
            break;
        case 3:
            printf("Merci de nous rendre visite");
            break;
        default :
            printf("ce choix n'existe pas, essayez-en un autre\n");
            break;
    }
    }while(choix!=3);

}

void sign_up(){
    struct clients newuser;
    printf("entrez vos informations maintenant \n");
    printf("\nvotre nom: ");
    scanf(" %[^\n]",newuser.nom);
    printf("votre prenom: ");
    scanf(" %[^\n]",newuser.prenom);
    printf("nom d'utilisateur: ");
    scanf(" %[^\n]",newuser.identifiant);
    printf("votre numero de telephone: ");
    scanf(" %[^\n]",newuser.tele);
    printf("votre mot de passe: ");
    scanf(" %[^\n]",newuser.mot_de_passe);

    data[countclients] = newuser ;
    countclients++;
    printf("vous avez cree un compte avec succes\n");
}

void menu_user() {
    int choix;
    printf("bienvenue sur notre site de gerer les reclamations de notre clients\n");
    printf("voulez-vous : \n");
    do{
        printf(" (1) creer un compte\n");
        printf(" (2) se connecter\n");
        printf(" (3) quitter le programme\n");
        scanf("%d",&choix);
        switch (choix){
            case 1 : 
                sign_up();
                break;
            case 2 :
               // sign_in();
                break;
            case 3:
                break;
            default :
                printf("ce choix n'existe pas, essayez-en un autre\n");
                break;
        }       
    }while(choix!=3);
}


int main(){

    menu_user();

    return 0;
}