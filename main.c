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
    int reussites;
    float somme_des_notes;
    float moyenne_generale;
};

struct Etudiant etudiants[200];
int size_etudiants = 0;
int id = 1;
struct Etudiant reussites[200];
int size_reussites = 0;

struct Departement departements[20];
int size_departements = 0;

void obtenir_departement()
{
    // reset departements comme vide
    memset(departements, 0, sizeof(departements));
    size_departements = 0;
    for (int i = 0; i < size_etudiants; i++)
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
                    departements[j].reussites++;
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
                departement.reussites = 1;
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
    etudiants[size_etudiants].id = id++;
    printf("saisir le nom:\n");
    scanf("%[^\n]", etudiants[size_etudiants].nom);
    getchar();
    printf("saisir le prenom:\n");
    scanf("%[^\n]", etudiants[size_etudiants].prenom);
    getchar();
    printf("saisir la date de naissance  JJ/MM/AAAA:\n");
    scanf("%[^\n]", etudiants[size_etudiants].date_de_naissance);
    getchar();
    printf("saisir le departement (PC, CH, MATH, BIO, INFO, ECO, PHILO..):\n");
    scanf("%[^\n]", etudiants[size_etudiants].departement);
    getchar();
    printf("saisir la note generale:\n");
    scanf("%f", &etudiants[size_etudiants].note_generale);
    getchar();
    size_etudiants++;
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
        printf("choix non valide!\n");
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
    for (int i = 0; i < size_etudiants; i++)
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
        printf("saisir la date de naissance  JJ/MM/AAAA:\n");
        scanf("%[^\n]", etudiants[indice].date_de_naissance);
        getchar();
        printf("saisir le departement (PC, CH, MATH, BIO, INFO, ECO, PHILO..):\n");
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
    int choix;
    printf("---------------\n");
    printf("[1] Supprimer.\n");
    printf("[2] Annuler.\n");
    printf("---------------\n");
    scanf("%d", &choix);
    getchar();

    if (indice != -1 && choix == 1)
    {
        for (int i = indice; i < size_etudiants - 1; i++)
        {
            etudiants[i] = etudiants[i + 1];
        }
        size_etudiants--;
        obtenir_departement();
    }
}

void afficher(struct Etudiant etudiants[200], int size_etudiants)
{
    if (size_etudiants > 0)
    {

        printf("-------------------------------------------------------------------------\n");
        printf("| %-4s | %-10s | %-10s | %-13s | %-12s | %-6s |\n",
               "ID", "Nom", "Prenom", "ne a", "Departement", "Note");
        printf("-------------------------------------------------------------------------\n");

        for (int i = 0; i < size_etudiants; i++)
        {
            printf("| %-4d | %-10s | %-10s | %-12s | %-12s | %-6.2f |\n",
                   etudiants[i].id,
                   etudiants[i].nom,
                   etudiants[i].prenom,
                   etudiants[i].date_de_naissance,
                   etudiants[i].departement,
                   etudiants[i].note_generale);
        }

        printf("-------------------------------------------------------------------------\n");
    }
    else
    {
        printf("===> Aucun etudiant trouve!\n");
    }
}

void calculer_moyenne_generale()
{
    if (size_etudiants != 0)
    {
        float somme_moyennes_generale = 0;
        for (int i = 0; i < size_departements; i++)
        {
            printf("La moyenne generale du departement %s: %.2f\n", departements[i].departement, departements[i].moyenne_generale);
            somme_moyennes_generale += departements[i].moyenne_generale;
        }
        printf("=> La moyenne generale d universite: %.2f\n", somme_moyennes_generale / size_departements);
    }
    else
    {
        printf("******* aucun etudiants trouve ********\n");
    }
}

void afficher_les_statistiques()
{
    if (size_etudiants == 0)
    {
        printf("****** aucun etudiants trouve *******\n");
    }
    else
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
            printf("#Le nombre total d etudiants: %d\n", size_etudiants);
            break;
        case 2:
            for (int i = 0; i < size_departements; i++)
            {
                printf("=> Le departement %s: %d.\n", departements[i].departement, departements[i].compteur);
            }

            break;
        case 3:
        {
            printf("saisir la seuil:\n");
            float seuil;
            scanf("%f", &seuil);
            getchar();
            printf("-------------------------------------------------------------------------\n");
            printf("| %-4s | %-10s | %-10s | %-13s | %-12s | %-6s |\n",
                   "ID", "Nom", "Prenom", "ne a", "Departement", "Note");
            printf("-------------------------------------------------------------------------\n");

            for (int i = 0; i < size_etudiants; i++)
            {
                if (etudiants[i].note_generale >= seuil)
                {

                    printf("| %-4d | %-10s | %-10s | %-12s | %-12s | %-6.2f |\n",
                           etudiants[i].id,
                           etudiants[i].nom,
                           etudiants[i].prenom,
                           etudiants[i].date_de_naissance,
                           etudiants[i].departement,
                           etudiants[i].note_generale);
                }
            }
            printf("-------------------------------------------------------------------------\n");
        }

        break;
        case 4:
        {
            struct Etudiant copie_etudiants[size_etudiants];
            for (int i = 0; i < size_etudiants; i++)
            {
                copie_etudiants[i] = etudiants[i];
            }

            int i = 1;
            printf("-------------------------------------------------------------------------\n");
            printf("| %-4s | %-10s | %-10s | %-13s | %-12s | %-6s |\n",
                   "ID", "Nom", "Prenom", "ne a", "Departement", "Note");
            printf("-------------------------------------------------------------------------\n");
            while (i <= 3 && i <= size_etudiants)
            {
                int max_indice = 0;
                for (int j = 1; j < size_etudiants; j++)
                {
                    if (copie_etudiants[max_indice].note_generale < copie_etudiants[j].note_generale)
                    {
                        max_indice = j;
                    }
                }
                copie_etudiants[max_indice].note_generale = 0;

                printf("| %-4d | %-10s | %-10s | %-12s | %-12s | %-6.2f |\n",
                       etudiants[max_indice].id,
                       etudiants[max_indice].nom,
                       etudiants[max_indice].prenom,
                       etudiants[max_indice].date_de_naissance,
                       etudiants[max_indice].departement,
                       etudiants[max_indice].note_generale);

                i++;
            }
            printf("-------------------------------------------------------------------------\n");
        }
        break;
        case 5:
            printf("Le nombre d etudiants ayant reussi dans chaque departement: \n");
            for (int i = 0; i < size_departements; i++)
            {
                printf("#departement %s: %d\n", departements[i].departement, departements[i].reussites);
            }

            break;

        default:
            printf("choix non valide!");
            break;
        }
    }
}

void rechercher()
{
    if (size_etudiants > 0)
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
            int trouve = 0;
            for (int i = 0; i < size_etudiants; i++)
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
                    trouve = 1;
                }
            }
            if (trouve == 0)
            {
                printf("**** aucun etudiant trouve avec ce nom! ****\n");
            }
        }

        break;
        case 2:
        {
            char departement[100];
            printf("Saisir le departement (PC, CH, MATH, BIO, INFO, ECO, PHILO..):");
            scanf("%s", &departement);
            int z = 1;
            for (int j = 0; j < size_etudiants; j++)
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
            printf("choix non valide!");
            break;
        }
    }
    else
    {
        printf("****** aucun etudiants trouve *******\n");
    }
}

void tri_alpha(struct Etudiant arr[], int n)
{
    struct Etudiant temp;
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(arr[j].nom, arr[minIdx].nom) < 0)
            {
                minIdx = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = temp;
    }
}
void tri_croissante(struct Etudiant arr[], int n)
{
    int min_indice;
    struct Etudiant temp;
    for (int i = 0; i < n - 1; i++)
    {
        min_indice = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j].note_generale < arr[min_indice].note_generale)
            {
                min_indice = j;
            }
        }

        temp = arr[i];
        arr[i] = arr[min_indice];
        arr[min_indice] = temp;
    }
}
void tri_decroissante(struct Etudiant arr[], int n)
{
    int max_indice;
    struct Etudiant temp;

    for (int i = 0; i < n - 1; i++)
    {
        max_indice = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j].note_generale > arr[max_indice].note_generale)
            {
                max_indice = j;
            }
        }

        temp = arr[i];
        arr[i] = arr[max_indice];
        arr[max_indice] = temp;
    }
}

void trier()
{
    int choix;
    printf("****  saisir votre choix  ****\n");
    printf("[1] Tri alphabetique des etudiants en fonction de leur nom.\n");
    printf("[2] Tri par moyenne generale decroissante.\n");
    printf("[3] Tri par moyenne generale croissante.\n");
    printf("[4] Tri des etudiants selon leur statut de reussite.\n");
    scanf("%d", &choix);
    getchar();
    if (size_etudiants == 0)
        printf("===> Aucun etudiant trouve!\n");
    else
    {

        switch (choix)
        {
        case 1:
            tri_alpha(etudiants, size_etudiants);
            afficher(etudiants, size_etudiants);
            break;
        case 2:
            tri_decroissante(etudiants, size_etudiants);
            afficher(etudiants, size_etudiants);
            break;
        case 3:
            tri_croissante(etudiants, size_etudiants);
            afficher(etudiants, size_etudiants);
            break;
        case 4:
            tri_decroissante(etudiants, size_etudiants);
            printf("-------------------------------------------------------------------------\n");
            printf("| %-4s | %-10s | %-10s | %-13s | %-12s | %-6s |\n",
                   "ID", "Nom", "Prenom", "ne a", "Departement", "Note");
            printf("-------------------------------------------------------------------------\n");

            for (int i = 0; i < size_etudiants; i++)
            {
                if (etudiants[i].note_generale < 10)
                    return;
                printf("| %-4d | %-10s | %-10s | %-12s | %-12s | %-6.2f |\n",
                       etudiants[i].id,
                       etudiants[i].nom,
                       etudiants[i].prenom,
                       etudiants[i].date_de_naissance,
                       etudiants[i].departement,
                       etudiants[i].note_generale);
            }

            printf("-------------------------------------------------------------------------\n");
            break;
        default:
            printf("choix non valide!");
            break;
        }
    }
}

void afficher_menu()
{
    int choix;
    printf("---------------------------------------\n");
    printf("****  Veuiller saisir votre choix  ****\n");
    printf("[1] Ajouter un etudiant.\n");
    printf("[2] Modifier un etudiant.\n");
    printf("[3] Supprimer un etudiant.\n");
    printf("[4] Afficher les details des etudiants. \n");
    printf("[5] Calculer la moyenne generale.\n");
    printf("[6] Afficher les statistiques\n");
    printf("[7] Rechercher un etudiant.\n");
    printf("[8] Trier les etudiants.\n");
    printf("[0] Quitter.\n");
    printf("---------------------------------------\n");

    scanf("%i", &choix);
    int quitter = 0;
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
        afficher(etudiants, size_etudiants);
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
    case 8:
        trier();
        break;
    case 0:
        quitter = 1;
        break;

    default:
        printf("Saisir un choix valide: entre 1 et 8\n");
        break;
    }

    if (quitter == 1)
        return;
    afficher_menu();
}

int main()
{
    struct Etudiant e1 = {1, "akraou", "ayoub", "02/05/2001", "INFO", 16};
    etudiants[size_etudiants] = e1;
    size_etudiants++;
    id++;
    struct Etudiant e2 = {2, "alaoui", "karim", "11/12/2003", "MATH", 12.5};
    etudiants[size_etudiants] = e2;
    size_etudiants++;
    id++;
    struct Etudiant e3 = {3, "badri", "yakout", "09/11/2000", "PC", 8};
    etudiants[size_etudiants] = e3;
    size_etudiants++;
    id++;
    struct Etudiant e4 = {4, "boutalbi", "mohamed", "13/09/2001", "INFO", 14};
    etudiants[size_etudiants] = e4;
    size_etudiants++;
    id++;
    struct Etudiant e5 = {5, "jeddar", "safaa", "29/10/1997", "MATH", 19};
    etudiants[size_etudiants] = e5;
    size_etudiants++;
    id++;
    struct Etudiant e6 = {6, "noumri", "oualid", "05/07/1999", "INFO", 9.5};
    etudiants[size_etudiants] = e6;
    size_etudiants++;
    id++;
    obtenir_departement();
    afficher_menu();
    return 0;
}
