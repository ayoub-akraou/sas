#include <stdio.h>
#include <string.h>

struct Etudiant
{
    int id;
    char nom[100];
    char prenom[100];
    char date_de_naissance[100];
    char departement[100];
    float note_generale;
};

struct Departement
{
    char departement[100];
    int compteur;
    int Reussites;
    float somme_des_notes;
    float moyenne_generale;
};

struct Etudiant etudiants[200];
int size = 0;

struct Departement departements[100];
int size_departements = 0;

void obtenir_departement()
{
    memset(departements, 0, sizeof(departements));
    size_departements = 0;
    for (int i = 0; i < size; i++)
    {
        int deja_existe = 0;
        for (int j = 0; j < size_departements; j++)
        {
            if (strcmp(etudiants[i].departement, departements[j].departement) == 0)

            {
                deja_existe = 1;
                departements[j].compteur++;
                if (etudiants[i].note_generale >= 10)
                {
                    departements[j].Reussites++;
                }
                departements[j].somme_des_notes += etudiants[i].note_generale;
                departements[j].moyenne_generale = departements[j].somme_des_notes / departements[j].compteur;
            }
        }
        if (deja_existe == 0)
        {
            struct Departement departement;
            strcpy(departement.departement, etudiants[i].departement);

            departement.compteur = 1;
            if (etudiants[i].note_generale >= 10)
            {
                departement.Reussites = 1;
            }

            departement.somme_des_notes = etudiants[i].note_generale;
            departement.moyenne_generale = departement.somme_des_notes / departement.compteur;

            departements[size_departements] = departement;
            size_departements++;
        }
    }
}

void ajouter_un_etudiant()
{
    etudiants[size].id = size;
    printf("saisir le nom:\n");
    scanf("%[^\n]", etudiants[size].nom);
    getchar();
    printf("saisir le prenom:\n");
    scanf("%[^\n]", etudiants[size].prenom);
    getchar();
    printf("saisir la date de naissance:\n");
    scanf("%[^\n]", etudiants[size].date_de_naissance);
    getchar();
    printf("saisir le departement:\n");
    scanf("%[^\n]", etudiants[size].departement);
    getchar();
    printf("saisir la note generale:\n");
    scanf("%f", &etudiants[size].note_generale);
    getchar();
    size++;
}

void ajouter()
{
    int choix;
    printf("****  Veuiller saisir votre choix  ****\n");
    printf("[1] ajouter un seul etudiant.\n");
    printf("[2] ajouter multiple etudiants.\n");
    scanf("%d", &choix);
    getchar();

    printf("=> choix:%d\n", choix);

    switch (choix)
    {
    case 1:
        ajouter_un_etudiant();
        break;
    case 2:
    {
        int n;
        printf("saisir le nombre des etudiants.\n");
        scanf("%d", &n);
        getchar();
        printf("=> nombres des  etudiants:%d\n", n);
        for (int i = 0; i < n; i++)
        {
            printf("#Etudiant %d:\n", i + 1);
            ajouter_un_etudiant();
        }
    }
    break;

    default:
        printf("choix non valide!");
        break;
    }
    obtenir_departement();
}

int rechercher_par_id()
{
    int id;
    printf("Saisir le id d'etudiant:\n");
    scanf("%d", &id);
    getchar();
    for (int i = 0; i < size; i++)
    {
        if (etudiants[i].id == id)
            return i;
    }
    printf("Aucun etudiant trouve avec ce (id)!\n");
    return -1;
}

void modifier()
{
    int indice = rechercher_par_id();
    if (indice != -1)
    {
        printf("saisir le nom:\n");
        scanf("%[^\n]", etudiants[indice].nom);
        getchar();
        printf("saisir le prenom:\n");
        scanf("%[^\n]", etudiants[indice].prenom);
        getchar();
        printf("saisir la date de naissance:\n");
        scanf("%[^\n]", etudiants[indice].date_de_naissance);
        getchar();
        printf("saisir le departement:\n");
        scanf("%[^\n]", etudiants[indice].departement);
        getchar();
        printf("saisir la note generale:\n");
        scanf("%f", &etudiants[indice].note_generale);
        getchar();
    }
    obtenir_departement();
}

void supprimer()
{
    int indice = rechercher_par_id();
    if (indice != -1)
    {
        for (int i = indice; i < size - 1; i++)
        {
            etudiants[i] = etudiants[i + 1];
            etudiants[i].id = i;
        }
        size--;
    }
    obtenir_departement();
}

void afficher()
{
    if (size == 0)
        printf("===> Aucun etudiant trouve!\n");
    for (int i = 0; i < size; i++)
    {
        printf("---------------------\n");
        printf("# Etudiant %d:\n", i + 1);
        printf(" id: %i\n", etudiants[i].id);
        printf(" Nom: %s\n", etudiants[i].nom);
        printf(" Prenom: %s\n", etudiants[i].prenom);
        printf(" Date de naissance: %s\n", etudiants[i].date_de_naissance);
        printf(" Departement: %s\n", etudiants[i].departement);
        printf(" Note generale: %.2f\n", etudiants[i].note_generale);
        printf("---------------------\n");
    }
}

void calculer_moyenne_generale()
{
    float somme_moyennes_generale = 0;
    for (int i = 0; i < size_departements; i++)
    {
        printf("La moyenne generale du departement %s: %.2f\n", departements[i].departement, departements[i].moyenne_generale);
        somme_moyennes_generale += departements[i].moyenne_generale;
    }
    printf("=> La moyenne generale d universite: %.2f\n", somme_moyennes_generale / size_departements);
}

void afficher_les_statistiques()
{
    int choix;
    printf("**** saisir votre choix  ****\n");
    printf("[1] Afficher le nombre total d etudiants inscrits.\n");
    printf("[2] Afficher le nombre d etudiants dans chaque departement.\n");
    printf("[3] Afficher les etudiants ayant une moyenne generale superieure a un certain seuil.\n");
    printf("[4] Afficher les 3 etudiants ayant les meilleures notes.\n");
    printf("[5] Afficher le nombre d etudiants ayant reussi dans chaque departement.\n");
    scanf("%d", &choix);
    getchar();

    switch (choix)
    {
    case 1:
        printf("#Le nombre total d etudiants: %d\n", size);
        break;
    case 2:
        for (int i = 0; i < size_departements; i++)
        {
            printf("=> Le departement de %s: %d.\n", departements[i].departement, departements[i].compteur);
        }

        break;
    case 3:
    {
        printf("saisir la seuil:\n");
        float seuil;
        scanf("%f", &seuil);
        getchar();
        for (int i = 0; i < size; i++)
        {
            if (etudiants[i].note_generale > seuil)
                printf("%d %s %s: %.2f\n", etudiants[i].id + 1, etudiants[i].nom, etudiants[i].prenom, etudiants[i].note_generale);
        }
    }

    break;
    case 4:
    {
        struct Etudiant copie_etudiants[size];
        for (int i = 0; i < size; i++)
        {
            copie_etudiants[i] = etudiants[i];
        }

        int i = 1;
        while (i <= 3)
        {
            int max_indice = 0;
            for (int j = 1; j < size; j++)
            {
                if (copie_etudiants[max_indice].note_generale < copie_etudiants[j].note_generale)
                {
                    max_indice = j;
                }
            }
            copie_etudiants[max_indice].note_generale = 0;
            printf("=> %d %s %s %.2f.\n", i, etudiants[max_indice].prenom, etudiants[max_indice].nom, etudiants[max_indice].note_generale);
            i++;
        }
    }
    break;
    case 5:
        printf("Le nombred etudiants ayant réussi dans chaque département: \n");
        for (int i = 0; i < size_departements; i++)
        {
            printf("#departement %s: %d\n", departements[i].departement, departements[i].Reussites);
        }

        break;

    default:
        break;
    }
}

void rechercher()
{
    int choix;
    printf("****  saisir votre choix  ****\n");
    printf("[1] Rechercher un etudiant par son nom.\n");
    printf("[2] Afficher la liste des etudiants inscrits dans un departement specifique\n");
    scanf("%d", &choix);
    getchar();
    switch (choix)
    {
    case 1:
    {
        char prenom[100];
        printf("saisir le prenom: ");
        scanf("%[^\n]", prenom);
        getchar();
        char nom[100];
        printf("saisir le nom: ");
        scanf("%[^\n]", nom);
        getchar();
        for (int i = 0; i < size; i++)
        {
            if (strcmp(etudiants[i].prenom, prenom) == 0 && strcmp(etudiants[i].nom, nom) == 0)
            {
                printf("-----------------\n");
                printf("id: %d.\n", etudiants[i].id);
                printf("nom: %s.\n", etudiants[i].nom);
                printf("prenom: %s.\n", etudiants[i].prenom);
                printf("date de naissance: %s.\n", etudiants[i].date_de_naissance);
                printf("departement: %s.\n", etudiants[i].departement);
                printf("note generale: %.2f.\n", etudiants[i].note_generale);
                printf("-----------------\n");
            }
        }
    }

    break;
    case 2:
    {
        char departement[100];
        printf("Saisir le departement:");
        scanf("%s", &departement);
        int z = 1;
        for (int j = 0; j < size; j++)
        {
            if (strcmp(departement, etudiants[j].departement) == 0)
            {
                printf("%d %s %s.\n", z, etudiants[j].nom, etudiants[j].prenom);
                z++;
            }
        }
    }
    break;

    default:
        break;
    }
}

void afficher_menu()
{
    int choix;
    printf("****  Veuiller saisir votre choix  ****\n");
    printf("[1] Ajouter un etudiant.\n");
    printf("[2] Modifier un etudiant.\n");
    printf("[3] supprimer un etudiant.\n");
    printf("[4] Afficher les details des etudiants. \n");
    printf("[5] Calculer la moyenne generale.\n");
    printf("[6] Afficher les statistiques\n");
    printf("[7] Rechercher un etudiant.\n");
    printf("[8] Trier les etudiants.\n");

    scanf("%i", &choix);
    getchar();

    switch (choix)
    {
    case 1:
        ajouter();
        break;
    case 2:
        modifier();
        break;
    case 3:
        supprimer();
        break;
    case 4:
        afficher();
        break;
    case 5:
        calculer_moyenne_generale();
        break;
    case 6:
        afficher_les_statistiques();
        break;
    case 7:
        rechercher();
        break;
        // case 8:
        //     trier();
        //     break;

    default:
        printf("Saisir un choix valide: entre 1 et 8\n");
        break;
    }

    afficher_menu();
}

int main()
{
    struct Etudiant e1 = {0, "akraou", "ayoub", "02/05/2001", "pc", 16};
    etudiants[size] = e1;
    size++;
    struct Etudiant e2 = {1, "alaoui", "karim", "11/12/2003", "x", 12.5};
    etudiants[size] = e2;
    size++;
    struct Etudiant e3 = {2, "badri", "ismail", "09/11/2000", "pc", 8};
    etudiants[size] = e3;
    size++;
    struct Etudiant e4 = {3, "boutalbi", "mohamed", "13/09/2001", "info", 14};
    etudiants[size] = e4;
    size++;
    struct Etudiant e5 = {4, "jeddar", "mounir", "29/10/1997", "info", 19};
    etudiants[size] = e5;
    size++;
    obtenir_departement();
    afficher_menu();
    return 0;
}
