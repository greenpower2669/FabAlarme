# FabAlarme
The program creates a minimalist user interface for a custom alert application called "FabAlarme." This interface allows users to set times for alerts and change the background color of the interface. It also offers options to activate or deactivate alerts through a simple graphical interface.


General Description
The program creates a minimalist user interface for a custom alert application called "FabAlarme." This interface allows users to set times for alerts and change the background color of the interface. It also offers options to activate or deactivate alerts through a simple graphical interface.

Key Features

Setting the Time and Alert: Users can enter a specific time to trigger an alert. The input fields only accept numbers for hours and minutes.
Alert Management: The application can activate or deactivate an alert based on the current time relative to the set time. When the alert time is reached, the background color of the user interface cycles through a predefined set of colors to draw the user's attention.
Customizable User Interface: Users can choose a color for the background of the user interface from a predefined set of colors.
Window Expansion Feature: The user interface can toggle between an expanded and a compact mode for better visibility or to save screen space.
Control Buttons: Buttons are available to close the application, open a settings dialog, and activate/deactivate the alert.


Technical Components

Event Management: The application uses a window procedure to handle events such as button clicks, text field entries, and menu commands.
Background Threads: A background thread is used to monitor the current time and compare it with the set time for the alert, adjusting the user interface accordingly.
Dynamic Color Management: The program dynamically changes the background color of the main window based on the active state of the alert, scrolling through a rainbow color palette.


Architecture

Use of Win32 API: The application is built using the classic Windows API (Win32), which allows it to be lightweight and responsive while offering extensive compatibility with Windows versions.
Internationalization: Strings are handled through direct calls, suggesting ease of internationalization by replacing texts with localized resources if necessary.


Practical Use

This application can be used for simple reminders in a work or home environment, allowing the user not to forget important events scheduled at specific times. It is particularly useful when the user needs strong visual alerts.

User Manual for FabAlarme Application
Requirements
Operating System: Windows.
Permissions: Administrator rights for installation.

Installation

Download the Installer: Obtain the installation file from the website or distribution media.
Run the Installer: Double-click the downloaded file and follow the on-screen instructions to install the application.


Starting the Application

Launch the application from the Start menu or the desktop shortcut.
Setting the Alarm


Open Alarm Settings:

Click the 'O' (Settings) button to open the settings dialog.
Select the hour and minutes for the alarm.
Choose the desired background color.
Click "Save" to apply the settings.
Activate/Deactivate the Alarm:
Click the '.' (Alert) button to toggle the alarm on or off.
When the alarm is active, the background color of the window will cycle through colors.


Stopping the Alarm

To stop an active alarm, click the 'X' (Close) button.
Closing the Application
Close the application by clicking the 'X' button or through the system menu.

FR:

application Windows développée en C++ utilisant l'API Win32. Voici une description détaillée de ses fonctionnalités et composants :

Description Générale
Le programme crée une interface utilisateur minimaliste pour une application d'alerte personnalisée, appelée "FabAlarme". Cette interface permet à l'utilisateur de définir des heures pour des alertes et de changer la couleur de fond de l'interface. Elle offre également des options pour activer ou désactiver des alertes à travers une interface graphique simple.

Fonctionnalités Clés

Définition de l'Heure et de l'Alerte : L'utilisateur peut entrer une heure spécifique pour déclencher une alerte. Les champs de saisie acceptent uniquement des chiffres pour les heures et les minutes.
Gestion des Alertes : L'application peut activer ou désactiver une alerte en fonction de l'heure actuelle par rapport à l'heure définie. Lorsque l'heure de l'alerte est atteinte, la couleur de fond de l'interface utilisateur change cycliquement à travers un ensemble de couleurs prédéfinies pour attirer l'attention de l'utilisateur.
Interface Utilisateur Personnalisable : Les utilisateurs peuvent choisir une couleur pour l'arrière-plan de l'interface utilisateur parmi un ensemble prédéfini de couleurs.
Fonctionnalité d'Expansion de Fenêtre : L'interface utilisateur peut basculer entre un mode agrandi et un mode compact pour une meilleure visibilité ou pour économiser de l'espace à l'écran.
Boutons de Contrôle : Des boutons sont disponibles pour fermer l'application, ouvrir un dialogue de paramètres, et activer/désactiver l'alerte.


Composants Techniques

Gestion des Événements : L'application utilise une procédure de fenêtre pour gérer les événements tels que les clics sur les boutons, la saisie dans les champs de texte, et les commandes de menu.
Threads en Arrière-Plan : Un thread en arrière-plan est utilisé pour surveiller l'heure actuelle et comparer avec l'heure définie pour l'alerte, ajustant l'interface utilisateur en conséquence.
Gestion Dynamique des Couleurs : Le programme change dynamiquement la couleur de fond de la fenêtre principale en fonction de l'état actif de l'alerte, faisant défiler une palette de couleurs de l'arc-en-ciel.


Architecture

Utilisation de l'API Win32 : L'application est construite en utilisant l'API Windows classique (Win32), ce qui lui permet d'être légère et réactive tout en offrant une compatibilité étendue avec les versions de Windows.
Internationalisation : Les chaînes sont gérées par des appels directs, suggérant une facilité d'internationalisation en remplaçant les textes par des ressources localisées si nécessaire.


Utilisation Pratique

Cette application peut être utilisée pour des rappels simples dans un environnement de travail ou domestique, permettant à l'utilisateur de ne pas oublier des événements importants programmés à des heures spécifiques. Elle est particulièrement utile lorsque l'utilisateur a besoin d'alertes visuelles fortes.


Mode d'emploi de l'application FabAlarme

Prérequis

Système d'exploitation : Windows.
Permissions : Droits d'administrateur pour l'installation.


Installation

Télécharger l'installateur : Obtenez le fichier d'installation depuis le site web ou le support de distribution.
Exécuter l'installateur : Double-cliquez sur le fichier téléchargé et suivez les instructions à l'écran pour installer l'application.


Démarrage de l'application

Lancez l'application depuis le menu Démarrer ou le raccourci sur le bureau.


Configuration de l'Alerte

Ouvrir les paramètres d'alerte :
Cliquez sur le bouton 'O' (Settings) pour ouvrir le dialogue des paramètres.
Sélectionnez l'heure et les minutes pour l'alerte.
Choisissez la couleur de fond souhaitée.
Cliquez sur "Enregistrer" pour appliquer les réglages.
Activer/désactiver l'alerte :
Cliquez sur le bouton '.' (Alerte) pour activer ou désactiver l'alerte.
Lorsque l'alerte est active, la couleur de fond de la fenêtre change cycliquement.


Arrêt de l'Alarme

Pour stopper une alerte active, cliquez sur le bouton 'X' (Close).
Fermeture de l'application
Fermez l'application en cliquant sur le bouton 'X' ou à travers le menu système.
