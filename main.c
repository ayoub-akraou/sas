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
    int reussissants;
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
                    departements[j].reussissants++;
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
                departement.reussissants = 1;
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
    printf("Aucun etudiant trouvé avec ce (id)!\n");
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
}

void supprimer()
{
    int indice = rechercher_par_id();
    if (indice != -1)
    {
        for (int i = indice; i < size - 1; i++)
        {
            etudiants[i] = etudiants[i + 1];
        }
        size--;
    }
}

void afficher()
{
    if (size == 0)
        printf("===> Aucun etudiant trouvé!\n");
    for (int i = 0; i < size; i++)
    {
        printf("---------------------\n");
        printf("# Etudiant %d:\n", i + 1);
        printf(" Nom: %s\n", etudiants[i].nom);
        printf(" Prenom: %s\n", etudiants[i].prenom);
        printf(" Date de naissance: %s\n", etudiants[i].date_de_naissance);
        printf(" Departement: %s\n", etudiants[i].departement);
        printf(" Note generale: %.2f\n", etudiants[i].note_generale);
        printf("---------------------\n");
    }
}

void afficher_menu()
{
    int choix;
    printf("****  Veuiller saisir votre choix  ****\n");
    printf("[1] Ajouter un étudiant.\n");
    printf("[2] Modifier un étudiant.\n");
    printf("[3] supprimer un étudiant.\n");
    printf("[4] Afficher les détails des étudiants. \n");
    printf("[5] Calculer la moyenne générale.\n");
    printf("[6] Afficher les statistiques\n");
    printf("[7] Rechercher un etudiant.\n");
    printf("[8] Trier les etudiants.\n");

    scanf("%i", &choix);
    getchar();
    printf("choix: %i\n\n", choix);

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
        // case 5:
        //     calculer_moyenne_generale();
        //     break;
        // case 6:
        //     afficher_les_statistiques();
        //     break;
        // case 7:
        //     rechercher();
        //     break;
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
    afficher_menu();
    return 0;
}
