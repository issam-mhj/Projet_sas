#include <stdio.h>
#include <string.h>
#include <unistd.h>

void menu_user();
void sign_up();
void sign_in();
int check_pass(char a[], char user[]);
void admin_menu();

int countclients = 0;
int isAdmin = 0;
char admin_user[]= "admin";
char admin_passw[]= "Admin.123";

struct clients
{
    char nom[20];
    char prenom[20];
    char identifiant[20];
    char tele[10];
    char mot_de_passe[30];
};

struct clients data[100];

// first page (menu)

void menu_user()
{
    int choix;
    printf("\nbienvenue sur notre site de gerer les reclamations de notre clients\n");
    printf("voulez-vous : \n");
    do
    {
        printf("\n (1) creer un compte\n");
        printf(" (2) se connecter\n");
        printf(" (3) quitter le programme\n");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            sign_up();
            break;
        case 2:
            sign_in();
            break;
        case 3:
            break;
        default:
            printf("ce choix n'existe pas, essayez-en un autre\n");
            break;
        }
    } while (choix != 3);
}

// check password in sign up

int check_pass(char a[], char user[])
{
    int i = 0, maj = 0, min = 0, dig = 0, char_sp = 0, somme = 0;
    if (strstr(a, user) != NULL)
    {
        return 0;
    }

    for (i = 0; a[i] != '\0'; i++)
    {
        if (a[i] >= 'A' && a[i] <= 'Z')
            maj = 1;
        if (a[i] >= 'a' && a[i] <= 'z')
            min = 1;
        if (a[i] >= '0' && a[i] <= '9')
            dig = 1;
        if (a[i] >= 33 && a[i] <= 47 || a[i] >= 58 && a[i] <= 64 || a[i] >= 91 && a[i] <= 96 || a[i] >= 123 && a[i] <= 126)
            char_sp = 1;
    }
    somme = maj + min + dig + char_sp;
    if (i < 8 || somme != 4)
        return 0;
    else
        return 1;
}

// sign up

void sign_up()
{
    struct clients newuser;
    int count = 0, checker;
    printf("entrez vos informations maintenant \n");
    printf("\nvotre nom: ");
    scanf(" %[^\n]", newuser.nom);
    printf("votre prenom: ");
    scanf(" %[^\n]", newuser.prenom);
    printf("nom d'utilisateur: ");
    scanf(" %[^\n]", newuser.identifiant);
    printf("numero de telephone: ");
    scanf(" %[^\n]", newuser.tele);
    do
    {
        if (count == 0)
            printf("mot de passe: ");
        else if (count == 1)
        {
            printf("essayez un autre mot de passe(Doit contenir au moins : Une lettre majuscule / Une lettre minuscule / Un chiffre / Un caractere special)");
            printf("8 caracteres minimale,Ne doit pas contenir le nom d'utilisateur\n");
        }
        else
            printf("essayez un autre mot de passe: \n");
        scanf(" %[^\n]", newuser.mot_de_passe);
        checker = check_pass(newuser.mot_de_passe, newuser.identifiant);
        count++;
    } while (checker == 0);
    data[countclients] = newuser;
    countclients++;
    printf("vous avez cree un compte avec succes\n");
    count = 0;
}

// sign in

void sign_in()
{
    char nom[30], password[30];
    int count, pass = 0;
    isAdmin=0;
    struct clients login;
    for (count = 0; count < 3; count++)
    {
        printf("entrez votre nom d'utilisateur: ");
        scanf(" %[^\n]", nom);
        printf("entrez votre mot de passe: ");
        scanf(" %[^\n]", password);
        if (strcmp(nom, admin_user) == 0 && strcmp(password, admin_passw)==0)
        {
            isAdmin=1;
            pass=1;
        }
        else
        {
            for (int i = 0; i < countclients; i++)
            {
                if (strcmp(data[i].identifiant, nom) == 0 && strcmp(data[i].mot_de_passe, password) == 0)
                {
                    printf("%s,vous etes connecte a votre compte ", data[i].prenom);
                    pass = 1;
                    break;
                }
            }
        }

        if (pass != 0)
            break;
        else
        {
            printf("Informations incorrectes, veuillez reessayer\n");
        }
    }

    if (pass == 1 && isAdmin ==1)
    {
        admin_menu();
    }
    if (count >= 3)
        printf("desole, vous avez depasse le nombre maximum de tentatives, reessayez plus tard\n");
    sleep(10);
}

//admin interface

void admin_menu(){
    int choix=0;
    printf("*****vous etes l'administrateur*****\n\n");
    do{
    printf("[1]  Ajouter une reclamation\n");
    printf("[2]  Afficher la liste des reclamations\n");
    printf("[3]  Modifier ou supprimer une reclamation\n");
    printf("[4]  Traiter une reclamation\n");
    printf("[5]  Rechercher une reclamation\n");
    printf("[6]  Systeme de priorite\n");
    printf("[7]  Afficher les reclamations ordonnees par priorite\n");
    printf("[8]  Se deconnecter\n");
    printf("votre choix= ");
    scanf("%d",&choix);
    switch (choix){
        case 1:
            // new_reclam();
            break;
        case 2:
            // affich_reclam();
            break;
        case 3:
            // edit_reclam();
            break;
        case 4:
            //traiter_reclam();
            break;
        case 5:
            //find_reclam();
            break;
        case 6:
            //syst_prior();
            break;
        case 7:
            //affich_byprio();
            break;
        case 8:
            printf("***Vous etes deconnecte***\n\n");
            break;
        default:
        printf("ce choix n'existe pas, essayez-en un autre\n");
        break;
    }
    }while(choix!=8);

    if (choix==8)
        menu_user();
}

int main()
{

    menu_user();

    return 0;
}