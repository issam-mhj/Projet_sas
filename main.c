#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void menu_user();
void sign_up();
void sign_in();
int check_pass(char a[], char user[]);
void admin_menu();
void new_reclam();
void affich_reclam();
void edit_reclam();
void traiter_reclam();
void find_reclam();
void gest_users();
void affich_byprio();
void agent_menu();
void client_menu();
void client_MS_reclam();
void stats_rapp();

int countclients = 0;
int countreclam = 0;
int count_resol_rec = 0;
int isAdmin = 0;
char admin_user[] = "admin";
char admin_passw[] = "Admin.123";
char prio_haute[] = {"urgence"};
char prio_haute2[] = {"dangereux"};
char prio_moyenne[] = {"crise"};
char prio_moyenne2[] = {"rapid"};
int current_user;
time_t date_after_resol;
time_t delayTime[100];

struct clients
{
    char nom[20];
    char prenom[20];
    char identifiant[20];
    char mot_de_passe[30];
    int client_type;
};

struct clients data[100];

struct reclamation
{
    int id;
    char which_user[20];
    char usernam[20];
    char motif[50];
    char description[200];
    char categorie[20];
    char status[20];
    char date[26];
    time_t date_int;
    char notes[100];
    char priorat[20];
};

struct reclamation reclamations[100];

// first page (menu)
void menu_user()
{
    int choix, count = 0;
    do
    {
        printf("\n------------------\n");
        printf("   voulez-vous    ");
        printf("\n------------------\n");
        printf("\n(1) creer un compte\n");
        printf("(2) se connecter\n");
        printf("(3) quitter le programme\n");
        printf("votre choix: ");
        scanf("%d", &choix);
        if (choix < 0 || choix > 9)
        {
            printf("ce choix n'existe pas, essayez-en un autre\n");
            break;
        }
        else
        {
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
                printf("\n//ce choix n'existe pas\\\\\n");
                printf("\\\\essayez-en un autre..//\n");
                break;
            }
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
    printf("\nentrez vos informations maintenant \n");
    printf("\nvotre nom: ");
    scanf(" %[^\n]", newuser.nom);
    printf("votre prenom: ");
    scanf(" %[^\n]", newuser.prenom);
    printf("nom d'utilisateur: ");
    scanf(" %[^\n]", newuser.identifiant);
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
    printf("\n[vous avez cree votre compte avec succes]\n");
    count = 0;
}

// sign in
void sign_in()
{
    char nom[30], password[30];
    int count, pass = 0;
    isAdmin = 0;
    struct clients login;
    for (count = 0; count < 3; count++)
    {
        printf("entrez votre nom d'utilisateur: ");
        scanf(" %[^\n]", nom);
        printf("entrez votre mot de passe: ");
        scanf(" %[^\n]", password);
        if (strcmp(nom, admin_user) == 0 && strcmp(password, admin_passw) == 0)
        {
            isAdmin = 1;
            pass = 1;
        }
        else
        {
            for (int i = 0; i < countclients; i++)
            {
                if (strcmp(data[i].identifiant, nom) == 0 && strcmp(data[i].mot_de_passe, password) == 0)
                {
                    printf("\n%s,vous etes connecte a votre compte \n", data[i].prenom);
                    if (data[i].client_type == 1)
                    {
                        isAdmin = 1;
                    }
                    else if (data[i].client_type == 2)
                    {
                        isAdmin = 2;
                    }
                    else
                    {
                        isAdmin = 3;
                        current_user = i;
                    }
                    pass = 1;
                    break;
                }
            }
        }

        if (pass != 0)
            break;
        else
        {
            printf("\nInformations incorrectes, veuillez reessayer\n");
        }
    }

    if (pass == 1 && isAdmin == 1)
    {
        admin_menu();
    }
    else if (pass == 1 && isAdmin == 2)
    {
        agent_menu();
    }
    else if (pass == 1 && isAdmin == 3)
    {
        client_menu();
    }

    if (count >= 3)
    {
        printf("\ndesole, vous avez depasse le nombre maximum de tentatives, reessayez apres 10 secondes\n");
        sleep(10);
    }

    count = 0;
}

// admin interface
void admin_menu()
{
    int choix = 0;
    printf("\n\n*****vous etes l'administrateur*****\n\n");
    do
    {
        printf("[1]  Ajouter une reclamation\n");
        printf("[2]  Afficher la liste des reclamations\n");
        printf("[3]  Modifier ou supprimer une reclamation\n");
        printf("[4]  Traiter une reclamation\n");
        printf("[5]  Rechercher une reclamation\n");
        printf("[6]  gestion des utilisateurs\n");
        printf("[7]  Afficher les reclamations ordonnees par priorite\n");
        printf("[8]  Statistiques et Rapports \n");
        printf("[9]  Se deconnecter\n");
        printf("votre choix= ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            new_reclam();
            break;
        case 2:
            affich_reclam();
            break;
        case 3:
            edit_reclam();
            break;
        case 4:
            traiter_reclam();
            break;
        case 5:
            find_reclam();
            break;
        case 6:
            gest_users();
            break;
        case 7:
            affich_byprio();
            break;
        case 8:
            stats_rapp();
            break;
        case 9:
            printf("***\nVous etes deconnecte***\n\n");
            break;
        default:
            printf("\nce choix n'existe pas, essayez-en un autre\n");
            break;
        }
    } while (choix != 9);
}

// ajjouter reclam
void new_reclam()
{
    struct reclamation new_reclam;
    char status[] = "en cours";
    char notes[100] = "aucune note pour le moment";
    srand(time(0));
    new_reclam.id = rand() % 1000;
    if (isAdmin == 3)
    {
        strcpy(new_reclam.which_user, data[current_user].identifiant);
    }
    strcpy(new_reclam.status, status);
    printf("\n----------------Ajouter votre reclamation---------------\n");
    printf("\n\nnom d'utilisateur\n");
    scanf(" %[^\n]", new_reclam.usernam);
    printf("\nentrez le motif de la reclamation \n");
    scanf(" %[^\n]", new_reclam.motif);
    printf("\n**********Description**********\n");
    scanf(" %[^\n]", new_reclam.description);
    printf("\n\nLa categorie de la reclamation\n");
    scanf(" %[^\n]", new_reclam.categorie);
    strcpy(new_reclam.notes, notes);
    if (strstr(new_reclam.description, prio_haute) != NULL || strstr(new_reclam.description, prio_haute2) != NULL)
    {
        strcpy(new_reclam.priorat, "haute");
    }
    else if (strstr(new_reclam.description, prio_moyenne) != NULL || strstr(new_reclam.description, prio_moyenne2) != NULL)
    {
        strcpy(new_reclam.priorat, "moyenne");
    }
    else
    {
        strcpy(new_reclam.priorat, "basse");
    }
    time_t time_now = time(NULL);
    new_reclam.date_int = time_now;
    strftime(new_reclam.date, 26, "%Y-%m-%d %H:%M:%S", localtime(&time_now));
    reclamations[countreclam] = new_reclam;
    countreclam++;
    printf("\n             votre reclamation a ete enregistree avec succes\n");
    printf("**********************************************************************\n");
}

// affiche la reclam
void affich_reclam()
{
    if (countreclam == 0)
    {
        printf("\n0 reclamation pour le moment\n\n");
    }
    else
    {
        for (int i = 0; i < countreclam; i++)
        {
            printf("\n-------------------------------------------------------------------\n");
            printf("ID du reclamation:              %d\n", reclamations[i].id);
            printf("le nom du client:               %s\n", reclamations[i].usernam);
            printf("notes pour cette reclamation    %s\n", reclamations[i].notes);
            printf("rempli le                       %s\n", reclamations[i].date);
            printf("Le motif de la reclamation      %s\n", reclamations[i].motif);
            printf("la priorite                    <%s>\n", reclamations[i].priorat);
            printf("\n[Descriptions]\n%s\n", reclamations[i].description);
            printf("\nLe statut de la reclamation=(%s)\n", reclamations[i].status);
            printf("----------------------------------------------------------------------\n");
        }
    }
}

// modifier ou supprime la reclam
void edit_reclam()
{
    int choice, idReclam, isfound = 0, ind_reclam = 0;
    time_t timenow;
    struct reclamation new_recl;
    printf("entrez ID de reclamation: \n");
    scanf("%d", &idReclam);
    for (int i = 0; i < countreclam; i++)
    {
        if (idReclam == reclamations[i].id)
        {
            printf("id est trouve");
            isfound = 1;
            ind_reclam = i;
            break;
        }
    }
    if (isfound == 1)
    {
        int choix;
        printf("\n (1) pour modifier la reclamation \n (2) pour supprimer la reclamation \nvotre choix: ");
        scanf("%d", &choix);
        if (choix == 1)
        {
            printf("voulez-vouz modifiez:\n");
            printf("   (1) Le motif\n   (2) Description\n   (3) Categorie\n");
            printf("votre choix: ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                char newmotif[50];
                printf("le motif: %s \n", reclamations[ind_reclam].motif);
                printf("entrez votre modification: ");
                scanf(" %[^\n]", newmotif);
                strcpy(reclamations[ind_reclam].motif, newmotif);
                timenow = time(NULL);
                new_recl.date_int = timenow;
                strftime(reclamations[ind_reclam].date, 26, "%Y-%m-%S %H:%M:%S", localtime(&timenow));
            }
            else if (choice == 2)
            {
                char new_descrip[200];
                printf("la description: %s \n", reclamations[ind_reclam].description);
                printf("entrez votre modification: ");
                scanf(" %[^\n]", new_descrip);
                strcpy(reclamations[ind_reclam].description, new_descrip);
                if (strstr(reclamations[ind_reclam].description, prio_haute) != NULL || strstr(reclamations[ind_reclam].description, prio_haute2) != NULL)
                {
                    strcpy(reclamations[ind_reclam].priorat, "haute");
                }
                else if (strstr(reclamations[ind_reclam].description, prio_moyenne) != NULL || strstr(reclamations[ind_reclam].description, prio_moyenne2) != NULL)
                {
                    strcpy(reclamations[ind_reclam].priorat, "moyenne");
                }
                else
                {
                    strcpy(reclamations[ind_reclam].priorat, "basse");
                }
                timenow = time(NULL);
                new_recl.date_int = timenow;
                strftime(reclamations[ind_reclam].date, 26, "%Y-%m-%S %H:%M:%S", localtime(&timenow));
            }
            else if (choice == 3)
            {
                char new_category[20];
                printf("la category: %s \n", reclamations[ind_reclam].categorie);
                printf("entrez votre modification: ");
                scanf(" %[^\n]", new_category);
                strcpy(reclamations[ind_reclam].categorie, new_category);
                timenow = time(NULL);
                new_recl.date_int = timenow;
                strftime(reclamations[ind_reclam].date, 26, "%Y-%m-%S %H:%M:%S", localtime(&timenow));
            }
            else
            {
                printf("\nce choix n'existe pas\n");
            }
        }
        else if (choix == 2)
        {
            int temp;
            for (int i = ind_reclam; i < countreclam - 1; i++)
            {
                reclamations[i] = reclamations[i + 1];
            }
            countreclam -= 1;
            printf("\nla reclamation a ete supprimee\n\n");
        }
        else
        {
            printf("\nce choix n'existe pas\n");
        }
    }
    else
    {
        printf("id n'est trouve pas");
    }
}

// traiter reclamations
void traiter_reclam()
{
    int idReclam, ind_reclam, isfound;
    printf("\nentrez ID de reclamation: \n");
    scanf("%d", &idReclam);
    for (int i = 0; i < countreclam; i++)
    {
        if (idReclam == reclamations[i].id)
        {
            printf("\nid est trouve\n");
            isfound = 1;
            ind_reclam = i;
            break;
        }
    }

    if (isfound == 1)
    {
        int choix = 0;
        printf("status actuel est :%s\n", reclamations[ind_reclam].status);
        printf("transferer a: \n (1) en cours\n (2) rejete\n (3) resolu \n");
        printf("votre choix: ");
        scanf("%d", &choix);
        if (choix == 1)
        {
            strcpy(reclamations[ind_reclam].status, "en cours");
            printf("\nle processus reussit\n\n");
        }
        else if (choix == 2)
        {
            strcpy(reclamations[ind_reclam].status, "rejete");
            printf("\nle processus reussit\n\n");
        }
        else if (choix == 3)
        {
            strcpy(reclamations[ind_reclam].status, "resolu");
            printf("\nle processus reussit\n\n");
            date_after_resol = time(NULL);
            delayTime[count_resol_rec] = date_after_resol - reclamations[ind_reclam].date_int;
            count_resol_rec++;
        }
        else
        {
            printf("\nce choix n'existe pas\n\n");
        }
        int notechoix = 0;
        char note[100];
        printf("voulez-vous ajouter une note?\n  (1) oui\t\t(2) non\nvotre choix: ");
        scanf("%d", &notechoix);
        if (notechoix == 1)
        {
            printf("\nla note exists maintenant: %s \n", reclamations[ind_reclam].notes);
            printf("entrez votre note: \n");
            scanf(" %[^\n]", note);
            strcpy(reclamations[ind_reclam].notes, note);
            printf("le changement est enregistre \n");
        }
    }
    else
    {
        printf("\nid n'est trouve pas\n");
    }
}

// find reclamation
void find_reclam()
{
    int choix, id;
    char nom[20], status[10], category[30], date[11];
    printf("\nvous pouvez rechercher par l'un des elements suivants:\n");
    printf("(1)id\t\t\t(2)nom du client\n");
    printf("(3)statut\t\t(4)categorie de reclamationt\n");
    printf("(5)date de soumission\t(6)pour quitter\n");
    printf("votre choix: ");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        printf("entrez l'id: \n");
        scanf("%d", &id);
        for (int i = 0; i < countreclam; i++)
        {
            if (reclamations[i].id == id)
            {
                printf("la/les reclamation/s a ete trouve \n");
                printf("ID du reclamation:%d\n", reclamations[i].id);
                printf("le nom du client:%s\n", reclamations[i].usernam);
                printf("la note : %s\n", reclamations[i].notes);
                printf("rempli le %s\n", reclamations[i].date);
                printf("Le motif de la reclamation %s\n", reclamations[i].motif);
                printf("**********Descriptions***********\n%s\n", reclamations[i].description);
                printf("la priorite: %s\n", reclamations[i].priorat);
                printf("Le statut de la reclamation=(%s)\n-----------------------------------------\n", reclamations[i].status);
                break;
            }
            else if (i == countreclam - 1)
            {
                printf("\nid n'est trouve pas\n");
            }
        }
        break;
    case 2:
        printf("entrez le nom du client: \n");
        scanf(" %[^\n]", nom);
        for (int i = 0; i < countreclam; i++)
        {
            if (strcmp(reclamations[i].usernam, nom) == 0)
            {
                printf("la/les reclamation/s a ete trouve \n");
                printf("ID du reclamation:%d\n", reclamations[i].id);
                printf("le nom du client:%s\n", reclamations[i].usernam);
                printf("la note : %s\n", reclamations[i].notes);
                printf("rempli le %s\n", reclamations[i].date);
                printf("Le motif de la reclamation %s\n", reclamations[i].motif);
                printf("**********Descriptions***********\n%s\n", reclamations[i].description);
                printf("la priorite: %s\n", reclamations[i].priorat);
                printf("Le statut de la reclamation=(%s)\n-----------------------------------------\n", reclamations[i].status);
            }
            else if (i == countreclam - 1)
            {
                printf("\nle nom n'est trouve pas\n");
            }
        }
        break;
    case 3:
        printf("entrez status du reclamation: \n");
        scanf(" %[^\n]", status);
        for (int i = 0; i < countreclam; i++)
        {
            if (strcmp(reclamations[i].status, status) == 0)
            {
                printf("la/les reclamation a ete trouve \n");
                printf("ID du reclamation:%d\n", reclamations[i].id);
                printf("le nom du client:%s\n", reclamations[i].usernam);
                printf("la note : %s\n", reclamations[i].notes);
                printf("rempli le %s\n", reclamations[i].date);
                printf("Le motif de la reclamation %s\n", reclamations[i].motif);
                printf("**********Descriptions***********\n%s\n", reclamations[i].description);
                printf("la priorite: %s\n", reclamations[i].priorat);
                printf("Le statut de la reclamation=(%s)\n-----------------------------------------\n", reclamations[i].status);
            }
            else if (i == countreclam - 1)
            {
                printf("\nstatus n'est trouve pas\n");
            }
        }
        break;
    case 4:
        printf("\nentrez categorie de reclamation : \n");
        scanf(" %[^\n]", category);
        for (int i = 0; i < countreclam; i++)
        {
            if (strcmp(reclamations[i].categorie, category) == 0)
            {
                printf("la/les reclamation/s a ete trouve \n");
                printf("ID du reclamation:%d\n", reclamations[i].id);
                printf("le nom du client:%s\n", reclamations[i].usernam);
                printf("la note : %s\n", reclamations[i].notes);
                printf("rempli le %s\n", reclamations[i].date);
                printf("Le motif de la reclamation %s\n", reclamations[i].motif);
                printf("**********Descriptions***********\n%s\n", reclamations[i].description);
                printf("la priorite: %s\n", reclamations[i].priorat);
                printf("Le statut de la reclamation=(%s)\n-----------------------------------------\n", reclamations[i].status);
            }
            else if (i == countreclam - 1)
            {
                printf("\nstatus n'est trouve pas\n");
            }
        }
        break;
    case 5:
        printf("entrez la date de reclamation (YYYY-MM-DD) : \n");
        scanf(" %[^\n]", date);
        for (int i = 0; i < countreclam; i++)
        {
            if (strstr(reclamations[i].date, date) != NULL)
            {
                printf("la/les reclamation a ete trouve \n");
                printf("ID du reclamation:%d\n", reclamations[i].id);
                printf("le nom du client:%s\n", reclamations[i].usernam);
                printf("la note : %s\n", reclamations[i].notes);
                printf("rempli le %s\n", reclamations[i].date);
                printf("Le motif de la reclamation %s\n", reclamations[i].motif);
                printf("**********Descriptions***********\n%s\n", reclamations[i].description);
                printf("la priorite: %s\n", reclamations[i].priorat);
                printf("Le statut de la reclamation=(%s)\n-----------------------------------------\n", reclamations[i].status);
            }
            else if (i == countreclam - 1)
            {
                printf("\nstatus n'est trouve pas\n");
            }
        }
        break;
    case 6:
        break;
    default:
        printf("ce demande n'existe pas\n");
        break;
    }
}

// gestions dusers
void gest_users()
{
    int choix;
    printf("    (1) affiche les utilisateurs\n");
    printf("    (2) donner un role\n");
    printf("votre choix: ");
    scanf("%d", &choix);
    if (choix == 1)
    {
        for (int i = 0; i < countclients; i++)
        {
            printf("(%d) : %s \n", i + 1, data[i].identifiant);
        }
    }
    else if (choix == 2)
    {
        struct clients role;
        int choice, admin_agent;
        char nom[20];
        printf("entrez le nom de l'utilisateur: \n");
        scanf(" %[^\n]", nom);
        for (int i = 0; i < countclients; i++)
        {
            if (strcmp(nom, data[i].identifiant) == 0)
            {
                printf("entrez [1] si vous voulez lui donner l'administrateur\n");
                printf("entrez [2] si vous voulez lui donner l'agent de reclamation\n");
                printf("entrez [3] si vous voulez lui donner normal client\n");
                scanf("%d", &admin_agent);
                if (admin_agent == 1)
                {
                    data[i].client_type = 1;
                }
                else if (admin_agent == 2)
                {
                    data[i].client_type = 2;
                }
                else
                {
                    data[i].client_type = 3;
                }
                break;
            }
            else if (i == countclients - 1)
            {
                printf("\nl'utilisateur n'a pas ete trouve\n");
            }
        }
    }
}

// triees en fonction de priorite
void affich_byprio()
{
    int i;
    printf("la priorite haute\n");
    for (i = 0; i < countreclam; i++)
    {
        if (strcmp(reclamations[i].priorat, "haute") == 0)
        {
            printf("-----------------------------------------\nla reclamation numero %d:\n", i + 1);
            printf("ID du reclamation:%d\n", reclamations[i].id);
            printf("le nom du client:%s\n", reclamations[i].usernam);
            printf("notes pour cette reclamation: %s\n", reclamations[i].notes);
            printf("rempli le \n");
            printf("Le motif de la reclamation %s\n", reclamations[i].motif);
            printf("**********Descriptions***********\n%s\n", reclamations[i].description);
            printf("la priorite : %s\n", reclamations[i].priorat);
            printf("Le statut de la reclamation=(%s)\n-----------------------------------------\n", reclamations[i].status);
        }
    }
    printf("la priorite moyenne:\n");
    for (i = 0; i < countreclam; i++)
    {
        if (strcmp(reclamations[i].priorat, "moyenne") == 0)
        {
            printf("-----------------------------------------\nla reclamation numero %d:\n", i + 1);
            printf("ID du reclamation:%d\n", reclamations[i].id);
            printf("le nom du client:%s\n", reclamations[i].usernam);
            printf("notes pour cette reclamation: %s\n", reclamations[i].notes);
            printf("rempli le \n");
            printf("Le motif de la reclamation %s\n", reclamations[i].motif);
            printf("**********Descriptions***********\n%s\n", reclamations[i].description);
            printf("la priorite : %s\n", reclamations[i].priorat);
            printf("Le statut de la reclamation=(%s)\n-----------------------------------------\n", reclamations[i].status);
        }
    }
    printf("la priorite basse:\n");
    for (i = 0; i < countreclam; i++)
    {
        if (strcmp(reclamations[i].priorat, "basse") == 0)
        {
            printf("-----------------------------------------\nla reclamation numero %d:\n", i + 1);
            printf("ID du reclamation:%d\n", reclamations[i].id);
            printf("le nom du client:%s\n", reclamations[i].usernam);
            printf("notes pour cette reclamation: %s\n", reclamations[i].notes);
            printf("rempli le \n");
            printf("Le motif de la reclamation %s\n", reclamations[i].motif);
            printf("**********Descriptions***********\n%s\n", reclamations[i].description);
            printf("la priorite : %s\n", reclamations[i].priorat);
            printf("Le statut de la reclamation=(%s)\n-----------------------------------------\n", reclamations[i].status);
        }
    }
}

// agent menu
void agent_menu()
{
    int choix = 0;
    printf("\n\n*****vous etes l'agent de reclamation*****\n\n");
    do
    {
        printf("[1]  Ajouter une reclamation\n");
        printf("[2]  Afficher la liste des reclamations\n");
        printf("[3]  Modifier ou supprimer une reclamation\n");
        printf("[4]  Traiter une reclamation\n");
        printf("[5]  Rechercher une reclamation\n");
        printf("[6]  Se deconnecter\n");
        printf("votre choix= ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            new_reclam();
            break;
        case 2:
            affich_reclam();
            break;
        case 3:
            edit_reclam();
            break;
        case 4:
            traiter_reclam();
            break;
        case 5:
            find_reclam();
            break;
        case 6:
            printf("***Vous etes deconnecte***\n\n");
            break;
        default:
            printf("ce choix n'existe pas, essayez-en un autre\n");
            break;
        }
    } while (choix != 6);
}

// client menu
void client_menu()
{
    int choix = 0;
    printf("*****\tbienvenue\t*****\n\n");
    do
    {
        printf("[1]  Ajouter une reclamation\n");
        printf("[2]  Modifier ou supprimer une reclamation\n");
        printf("[3]  Se deconnecter\n");
        printf("votre choix= ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            new_reclam();
            break;
        case 2:
            client_MS_reclam();
            break;
        case 3:
            printf("***Vous etes deconnecte***\n\n");
            break;
        default:
            printf("ce choix n'existe pas, essayez-en un autre\n");
            break;
        }
    } while (choix != 3);
}

// client modifier ou supprime ..
void client_MS_reclam()
{
    int choice, idReclam, isfound = 0, ind_reclam = 0;
    printf("votre reclamations :\n");
    for (int i = 0; i < countreclam; i++)
    {
        if (strcmp(reclamations[i].which_user, data[current_user].identifiant) == 0)
        {
            printf("-----------------------------------------\nla reclamation numero %d:\n", i + 1);
            printf("ID du reclamation:%d\n", reclamations[i].id);
            printf("le nom du client:%s\n", reclamations[i].usernam);
            printf("notes pour cette reclamation: %s\n", reclamations[i].notes);
            printf("rempli le \n");
            printf("Le motif de la reclamation %s\n", reclamations[i].motif);
            printf("**********Descriptions***********\n%s\n", reclamations[i].description);
            printf("la priorite : %s\n", reclamations[i].priorat);
            printf("Le statut de la reclamation=(%s)\n-----------------------------------------\n", reclamations[i].status);
        }
    }
    printf("entrez ID de reclamation: \n");
    scanf("%d", &idReclam);
    for (int i = 0; i < countreclam; i++)
    {
        if (idReclam == reclamations[i].id)
        {
            printf("id est trouve");
            isfound = 1;
            ind_reclam = i;
            break;
        }
    }
    if (isfound == 1)
    {
        int choix;
        time_t time_now = time(NULL);
        printf("\n (1) pour modifier la reclamation \n (2) pour supprimer la reclamation \nvotre choix: ");
        scanf("%d", &choix);
        if (difftime(time_now, reclamations[ind_reclam].date_int) >= 86400)
        {
            printf("\ndesole, vous avez depasse le temps minimum pour editer votre reclamation\n");
        }
        else if (choix == 1)
        {
            printf("voulez-vouz modifiez:\n");
            printf("   (1) Le motif:\n   (2)Description\n   (3)Categorie\n");
            printf("votre choix: ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                char newmotif[50];
                printf("le motif: %s \n", reclamations[ind_reclam].motif);
                printf("entrez votre modification: ");
                scanf(" %[^\n]", newmotif);
                strcpy(reclamations[ind_reclam].motif, newmotif);
            }
            else if (choice == 2)
            {
                char new_descrip[200];
                printf("la description: %s \n", reclamations[ind_reclam].description);
                printf("entrez votre modification: ");
                scanf(" %[^\n]", new_descrip);
                strcpy(reclamations[ind_reclam].description, new_descrip);
            }
            else if (choice == 3)
            {
                char new_category[20];
                printf("la category: %s \n", reclamations[ind_reclam].categorie);
                printf("entrez votre modification: ");
                scanf(" %[^\n]", new_category);
                strcpy(reclamations[ind_reclam].categorie, new_category);
            }
            else
            {
                printf("\nce choix n'existe pas\n");
            }
        }
        else if (choix == 2)
        {
            int temp;
            for (int i = ind_reclam; i < countreclam - 1; i++)
            {
                reclamations[i] = reclamations[i + 1];
            }
            countreclam -= 1;
            printf("\nla reclamation a ete supprimee\n");
        }
        else
        {
            printf("\nce choix n'existe pas\n");
        }
    }
    else
    {
        printf("id n'est trouve pas");
    }
}

//stats
void stats_rapp()
{
    int choice, taux = 0;
    int num_resolue = 0, num_of_delay = 0;
    printf("\n   (1) Afficher le nombre total de reclamations\n");
    printf("   (2) Afficher le taux de resolution des reclamations\n");
    printf("   (3) le delai moyen de traitement des reclamations\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("\n-----------------------------------------\n");
        printf("le nombre total de reclamations= %d", countreclam);
        printf("\n-----------------------------------------\n");
    }
    else if (choice == 2)
    {
        if (count_resol_rec == 0)
        {
            printf("\naucune resolu reclamation exist\n");
        }
        else
        {
            for (int i = 0; i < countreclam; i++)
            {
                if (strcmp(reclamations[i].status, "resolu") == 0)
                    num_resolue++;
            }
            taux = (num_resolue * 100) / countreclam;
            printf("\n-----------------------------------------");
            printf("\n-----------------------------------------\n");
            printf("le taux de resolution des reclamations= %d %%", taux);
            printf("\n-----------------------------------------");
            printf("\n-----------------------------------------\n");
        }
    }
    else if (choice == 3)
    {
        if (count_resol_rec == 0)
        {
            printf("\naucune resolu reclamation exist\n");
        }
        else
        {
            for (int i = 0; i < count_resol_rec; i++)
            {
                num_of_delay += delayTime[i];
            }
            printf("\nle delai moyen de traitement=%d s\n", num_of_delay / count_resol_rec);
        }
    }
    else
    {
        printf("\nce choix n'existe pas\n");
    }
}

//main.
int main()
{
    printf("\n\n\t<<< bienvenue sur notre site de gerer les reclamations de notre clients>>>\n\n\n");
    menu_user();

    return 0;
}
