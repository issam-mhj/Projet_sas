#include <stdio.h>
#include <string.h>

void menu_user();
void stats_rapp();
void sign_up();
void sign_in();
int check_pass();

int countclients = 0;

struct clients
{
    char nom[20];
    char prenom[20];
    char identifiant[20];
    char tele[10];
    char mot_de_passe[30];
};

struct clients data[100];

void menu()
{
    int choix;
    printf("voulez-vous : \n");
    do
    {
        printf("(1) Gestion des reclamations\n");
        printf("(2) Statistiques et Rapports\n");
        printf("(3) quitter le programme\n");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            // gestion_recl();
            break;
        case 2:
            // stats_rapp();
            break;
        case 3:
            printf("Merci de nous rendre visite");
            break;
        default:
            printf("ce choix n'existe pas, essayez-en un autre\n");
            break;
        }
    } while (choix != 3);
}

int check_pass(char a[])
{
    int i = 0, maj = 0, min = 0, dig = 0, char_sp = 0, somme = 0;
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

void sign_up()
{
    struct clients newuser;
    int count = 0, checker;
    char checker2;
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
        checker = check_pass(newuser.mot_de_passe);
        count++;
    } while (checker == 0);
    data[countclients] = newuser;
    countclients++;
    printf("vous avez cree un compte avec succes\n");
    count = 0;
}

void sign_in()
{
    char nom[30], password[30];
    int count, pass = 0;
    struct clients login;
    for (count = 0; count <= 3; count++)
    {
        printf("entrez votre nom d'utilisateur: ");
        scanf(" %[^\n]", nom);
        printf("entrez votre mot de passe: ");
        scanf(" %[^\n]", password);
        for (int i = 0; data[i].identifiant != '\0'; i++)
        {
            if (strcmp(data[i].identifiant, nom) == 0 && strcmp(data[i].mot_de_passe, password) == 0)
            {
                printf("%s,vous etes connecte a votre compte ", data[i].prenom);
                pass++;
                break;
                //the error is here
            }
        }
        if (pass != 0)
            break;
    }
    menu();
}

void menu_user()
{
    int choix;
    printf("bienvenue sur notre site de gerer les reclamations de notre clients\n");
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

int main()
{

    menu_user();

    return 0;
}