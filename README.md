# projetchat

Application de chat client-serveur en **C**, réalisée en licence d'informatique (programmation système et réseau).

## Description

Le serveur est découpé en trois processus créés par `fork()` et reliés par des tubes (`pipe`) :

- **communication** — accepte les clients et échange les messages (sockets TCP / UDP, un thread par client) ;
- **gestion** — gère les comptes : création, suppression, connexion, déconnexion, liste des utilisateurs ;
- **rmi** — passerelle vers un client Java RMI (ébauche, dans `maven_chat/`).

Les messages reçus sont rediffusés à l'ensemble des clients connectés.

## Organisation du dépôt

| Dossier | Contenu |
|---|---|
| `c_serveur/` | Serveur : `main.c` (processus), `communication.c`, `gestion.c`, `rmi.c` |
| `c_client/` | Client en ligne de commande |
| `maven_chat/` | Client Java RMI (Maven), inachevé |

## Technologies utilisées

C (POSIX : `fork`, `pipe`, threads, sockets, mémoire partagée) · Java / Maven pour la partie RMI

## Compiler et lancer

```bash
gcc c_serveur/*.c -o serveur -lpthread
gcc c_client/*.c -o client
./serveur        # dans un terminal
./client         # dans un autre
```

## Contact

**Auteur :** resendecode
**GitHub :** [github.com/resendecode](https://github.com/resendecode)
