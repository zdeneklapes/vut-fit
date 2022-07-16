/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file menu.cpp
 */

#include "src/gui/menu/menu.h"
#include "src/gui/window.h" // forward

Menu::Menu(Window *parent, Canvas *c) : QMenuBar(parent), side_toolbox(parent->side_toolbox),
                                        canvas(c) {
    create_actions();
    create_menu();
}

Menu::~Menu() {}

void Menu::help() {
    auto dialog = new QDialog(nullptr);
    auto layout = new QVBoxLayout();
    auto label = new QLabel(
            R"(
Authori projektu:
    - Andrej Bínovský (xbinov00)
    - Zdeněk Lapeš (xlapes02)

Plně funkční implementace:
    - Aplikace umožňuje načítat, editovat a ukládat diagramy tříd a sekvenční diagramy z jazyka UML.
    - Je možné vytvoření diagramu tříd a neomezený počet sekvenčních diagramů.
    - Při interaktivních zásazích je zohledněna provázanost diagramu tříd a sekvenčních diagramů. A to přesně:
       - změna názvu entity
       - změna názvu metody / zprávy
    - Diagram tříd:
       - Aplikace načte ze souboru textové parametry diagramu třídy a zobrazí jej se všemi potřebnými
         komponentami, tj. název třídy, atributy s datovými typy vč. podpory čtyř možných
         modifikátorů přístupu ( + , - , # , ~ ) a metody. Obdobně pro rozhraní.
       - Třídy/Rozhraní mohou být dále propojeny pomocí vztahů: asociace, agregace, kompozice a generalizace.
    - Sekvenční diagram:
        - Aplikace načte textové parametry sekvenčního diagramu a zobrazí jí se všemi potřebnými komponentami
          (časová osa, objekty).
        - Objekty mohou spolu dále interagovat pomocí zpráv, které mohou být těchto typů: synchronní zpráva, asynchronní
          zpráva, návrat zprávy, tvorba objektu.
        - Podporu aktivace, vytváření a rušení objektů.
    - Verifikace:
        - Aplikace před uložením zkontroluje validnost propojení diagramů:
            - Názvy entit musí být v diagramech unikátní.
            - Názvy entit v sekvencím diagramu musí existovat v diagramu tříd.
            - Názvy zpráv v sekvenčním diagramu musí existovat jako metody v diagramu tříd.
        - Aplikace upozorní na přesnou chybu v diagramu.

Nedostatky / neimplementované:
    - Aplikace podporuje vytváření diagramů vrámci jen jedné scény.
    - Aplikace nepodporuje zasílání a přijímání zprávy/vztahu v rámci jedné entity/třidy.
    - Funkce Undo je implementována pouze v ramci diagramu tříd a to na akce:
        - Přídání třídy v diagramu tříd (odebere přidanou třidu)
        - změna textu v třídě (vrátí změt změněný text)
        - Odebrání třidy (vytvoří třídu)
    - Aplikace nevaliduje při otevírání diagramu jeho korektnost. Tuto funkci jsme neimplementovali z důvodu kontroly
      diagramu před uložením.
    - V případě generalizace budou přepsané metody v odvozených třídách vizuálně odlišeny.

Popis:
    - Aplikace je tvořena z okna rozděleného do dvou částí:
         - První část okna tvoří boční panel. V panelu lze přepínat editaci mezi třídním a sekvenčním diagramem.
           Přepínání editace je implementováno pomocí tabů.
         - Druhou část okna tvoří scéna. Scéna zobrazuje prvky jednotlivých diagramů.

    - Aplikace podporuje vytváření diagramů vrámci jen jedné scény.

Otevírání / Ukládání souborů:
    - Soubory jsou ukladané ve formátě json.
    - Uložit nebo otevřít diagram můžeme v "menu" v záložce "File" pod názvem
      "Open File" a "Save File"
    - Klávesové zkratky: Open File: 'Ctrl' + 'O'
                         Save File: 'Ctrl' + 'S'

Verifikace:
    - Při otvaření diagramu ze souboru program počítá s již konzistentními a spravnými daty, protože
      tato kontrola se provádí již před ukládání.
    - Při zjištění nekonzistence je zobrezená chybova hláška a aplikace ukládaní neprovede.

Zoom in / Zoom out:
    - Aby se ve scéně lépe orientovalo, v aplikace je implementovaná funkcionalita
      přibližování a oddalování scény. Je dostupná z menu pod kolonkou "File".
    - Klavesové zkrátky: Zoom in : 'Ctrl' + '+'
                         Zoom out: 'Ctrl' + '-'

Vytváření diagramu tříd:
    - Program podporuje vytváření nekonečného množství tříd.

    - Třídy je možné přidávat kliknutím na tlačítko "Add Class", třída se
      vytvoří výchozými texty. První je vždy název třídy, následuje sekce s atributy
      a po ní je sekce s metodami.
    - Třídu je možné odstranit označením dané třídy a kliknutím na tlačítko "Delete Class".

    - Atributy:
        - Aby se do třídy vložil atribut je prvně nutné označit atribut, za který chcete nový
          atribut vložit (pokud chcete vložit nový atribut, jako první označte název třídy).
        - Mazání atributů funkuje obdobně, jako mazání třídy. Prvně je třeba označit atribut a poté
          kliknout na tlačítko "Delete Attribute".

    - Metody:
        - Přidávání a odebírání metod funkuje obdobně, jako přidávání a odebírání atributů. Prvně se
          vybere metoda, za kterou chcete novou metodu vložit (pokud chcete vložit metodu jako první je
          třeba označit poslední atribut), poté můžeme kliknout na tlačítko "Add Method".
        - Mazání funkuje stejně jako mazání atributů.

    - Vztahy tříd:
        - Pokud chceme třídy propojit nějakým vztahem musíme 2 třídy označit, vybrat v ComboBoxu
          typ 1.vztahu a typ 2.vztahu a poté kliknout na tlačítko "Connect Classes", ke vztahu se
          automaticky vytvoří název vztahu "relation name".
        - Pokud chcete vztah odstranit nebo změnit, prvně jej
          musíme označit a poté můžeme buď v ComboBoxu změnit typ vztahu a nebo kliknutím na tlačítko
          "Disconnect Classes" odstranit vztah.

    - Texty:
        - Pokud chcete ke vztahu přidat i kardinalitu je tu možnost přidat textové pole do scény.
        - Textové pole je editovatelné a pohybovatelné. Můžeme do něj napsat co chceme a přetáhnout
          ho kam chceme.
        - Pro odstranění je prvně opět nutné textové pole označit a kliknout na tlačítko "Delete Text Item".

Vytváření sekvenčního diagramu:
    - Diagram se automaticky vytvoří při přidání prvního prvku na scénu. Přidávání a editace prvku
      je možná přes boční panel s tlačítky.

    - Program podporuje vytváření neomezeného počtu sekvenčních diagramů.
        - Každý sekvenční diagram musí obsahovat název. První diagram má výchozí název "Default Name".
        - Při vytváření dalšího, nového sekvenčního diagramu stačí jednoduše změnit vstupní text "Working On Diagram" na
          nový název.
        - Při editaci více než jednoho sekvenčního diagramu je potřeba přepisovat vstupní text „Working On Diagram“.
          V tomto případě je někdy zdlouhavé a také obtížné si pamatovat všechny názvy diagramů. Proto jsme vytvořili
          tlačítko "Set Diagram By Entity". Abyste mohli přepnout editaci na daný diagram musíte nejprve vybrat
          entitu (Aktér nebo Objekt) a následně kliknout na tlačítko "Set Diagram By Entity". Po úspěšném přepnutí
          se ukáže nový název ve vstupním textu "Working On Diagram".

    - Vytváření nových objektů a aktérů.
        - Pro vytvoření nového aktéra je třeba mít zvolen správný název diagramu do kterého patří.
        - Po stlačení tlačítka "New Actor" se vytvoří nový aktér.
        - Po stlačení tlačítka "New Object" se vytvoří nový objekt.
        - Spolu s vytvořenými entitami se vytvoří jejich životní osa.

    - Životní osa entity (objektu a aktéra).
        - Životní osa je určena pro boxy reprezentující život entity a přijímání a odesílání zpráv.
        - Délka osy není statická a lze ji měnit.
        - Pro změnu délky všech os určitého diagramu je třeba vybrat jednu životní osu a následně změnit
          velikost pomocí posuvníku "Resizer".

    - Vytváření boxů, reprezentující život entity.
        - Pro vytvoření boxu je třeba vyjmout  životou osu, následně kliknout na tlačítko "New Box".
        - Pro změnu délky boxu je třeba vybrat box a následně změnit velikost pomocí posuvníku.

    - Vytváření zpráv.
        - Pro vytvoření zprávy je třeba:
            - Do vstupního textu "Entity From" zadat jméno entity ze které je zpráva volána.
            - Do vstupního textu "Entity To" zadat jméno entity která zprávu přijímá.
            - Následně stisknout tlačítko s přesným typem zprávy kterou chcete vytvořit.
        - Pro přesouvání zprávy po životní ose slouží červené tlačítko na začátku každé zprávy.

    - Mazání prvků
        - Pro smazání jakéhokoli prvku na scéně je třeba vybrat prvek a následně stačit tlačítko "Delete".
        - Při smazání entity se automaticky smažou zprávy a boxy které patří životní ose entity.

Copyright / inspirace:
    - https://stackoverflow.com/a/32198716
    - http://www.fit.vutbr.cz/study/courses/ICP/public/.cs
    - https://zetcode.com/gui/qt5/
    - https://doc.qt.io/qt-6/qtexamples.html
)");
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(label);
    layout->addWidget(scrollArea);
    dialog->setLayout(layout);
    dialog->show();
}

void Menu::create_actions() {
    open_file_act = new QAction(tr("Open File"), this);
    save_file_act = new QAction(tr("Save File"), this);
    help_act = new QAction(tr("&Help"), this);
    zoom_in_act = new QAction(tr("Zoom In"), this);
    zoom_out_act = new QAction(tr("Zoom Out"), this);

    zoom_in_act->setShortcuts(QKeySequence::ZoomIn);
    zoom_in_act->setStatusTip(tr("Zoom In"));
    connect(zoom_in_act, &QAction::triggered, canvas, &Canvas::zoom_in);

    zoom_out_act->setShortcuts(QKeySequence::ZoomOut);
    zoom_out_act->setStatusTip(tr("Zoom In"));
    connect(zoom_out_act, &QAction::triggered, canvas, &Canvas::zoom_out);

    /* opening items to scene */
    auto open_file = new Open_file(side_toolbox->get_scene());
    open_file_act->setShortcuts(QKeySequence::Open);
    open_file_act->setStatusTip(tr("Open file"));
    connect(open_file_act, &QAction::triggered, open_file, &Open_file::open_file);

    /* saving items of scene */
    auto save_file = new Save_file(side_toolbox->get_scene());
    save_file_act->setShortcuts(QKeySequence::Save);
    save_file_act->setStatusTip(tr("Save file"));
    connect(save_file_act, &QAction::triggered, save_file, &Save_file::save_file);

    /* undo */
    undo_act = Window::stack->createUndoAction(this, tr("Undo"));
    undo_act->setShortcuts(QKeySequence::Undo);

    help_act->setStatusTip(tr("Show help"));
    connect(help_act, &QAction::triggered, this, &Menu::help);
}

void Menu::create_menu() {
    file_menu = new QMenu();
    help_menu = new QMenu();

    file_menu = this->addMenu(tr("File"));
    file_menu->addAction(open_file_act);
    file_menu->addAction(save_file_act);
    file_menu->addAction(undo_act);
    file_menu->addAction(zoom_in_act);
    file_menu->addAction(zoom_out_act);

    help_menu = this->addMenu(tr("Help"));
    help_menu->addAction(help_act);
}

void Menu::undo() {

}
