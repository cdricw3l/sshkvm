# 🎓 Plateforme de VM éducative sécurisée

Une plateforme sécurisée permettant aux élèves de créer et gérer leurs machines virtuelles via SSH, avec un accès strictement contrôlé et isolé.

## 🧠 Concept

La plateforme repose sur :

🖥️ Virtualisation via KVM
🔐 Accès contrôlé via OpenSSH
💾 Stockage léger avec SQLite

Chaque élève peut :

Créer une VM
Démarrer / arrêter sa VM
Gérer des snapshots
Interagir uniquement via des commandes autorisées

# ⚙️ 1. Installation de KVM
## 📦 Installation des dépendances
```
sudo apt -y install bridge-utils cpu-checker libvirt-clients libvirt-daemon qemu qemu-kvm
``` 
## 🔍 Vérification de la virtualisation
```
kvm-ok
```
✅ Résultat attendu

```
    INFO: /dev/kvm exists
    KVM acceleration can be used
```

# 💾 2. Installation de SQLite

```
    sudo apt update
    sudo apt install sqlite3
    sudo apt install libsqlite3-dev
```

👉 libsqlite3-dev permet d’utiliser l’API SQLite dans ton programme (C, etc.)

# 🔐 3. Configuration de SSH

L’objectif est de forcer l’exécution d’un programme de dispatch et d’interdire tout accès shell.

## 🧑‍💻 Utilisateurs:
    * student → accès restreint (élèves)
    * direction → accès complet (administration)

🛠️ Configuration /etc/ssh/sshd_config

```
    Match User student
        X11Forwarding no
        AllowTcpForwarding no
        PermitTTY no
        ForceCommand /home/student/test.sh
```

🔒 Effet de cette configuration

Pour l’utilisateur student :

    ❌ Pas de shell interactif
    ❌ Pas de ls, cd, etc.
    ❌ Pas de tunnel SSH
    ✅ Exécution automatique du programme test.sh

🧪 Exemple de connexion:

```
ssh student@192.168.1.10
```

👉 Lance automatiquement :
```
/home/student/test.sh
```

## 👨‍💼 Accès administrateur

L’utilisateur direction :

    * Peut se connecter normalement via SSH
    * Dispose d’un shell complet
    * Gère l’infrastructure

# ⚙️ 4. Rôle du programme de dispatch

Le script (ou programme) test.sh agit comme un contrôleur central.

## 🎯 Fonctions possibles
```
    Création de VM
    Démarrage / arrêt
    Snapshot
    Suppression
``` 

# 🔥 Architecture globale

```
    [ Client SSH ]
            ↓
    [ OpenSSH (ForceCommand) ]
            ↓
    [ Dispatch Program ]
            ↓
    [ KVM / libvirt ]
            ↓
    [ Machines Virtuelles ]
```