#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "GetFromFile.h"
static void HpSet(GtkWidget* spin, gpointer data)
	{
		data=(gint*)(int)gtk_adjustment_get_value(GTK_ADJUSTMENT(spin));
	}
static void AddMob(GtkWidget *table, int i,  const char* MobName, const char* mob)
	{
				i=2*i;
				int SHP=25;	
				int NuInit=0;
				//int SHP=StringToInt(GetFromFile("HIT", mob));	
				GtkWidget *name, *stats, *hp, *image, *spin, *initiative, *roll;
				std::string HP="Hit:";
				HP.append(GetFromFile("HIT", mob));	
				HP.append("/");	
				HP.append(std::to_string(SHP));	

				name=gtk_label_new(MobName);
				hp= gtk_progress_bar_new();
				gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(hp), 1.0);
				gtk_progress_bar_set_text(GTK_PROGRESS_BAR(hp), HP.c_str());
				image=gtk_image_new_from_file(GetFromFile("IMG", mob).c_str());
				gtk_widget_set_size_request(image, 64,64);
		
				roll = gtk_button_new_with_label("Roll initiative");


	
				GtkObject* HealthBar= gtk_adjustment_new(SHP, 0,StringToInt(GetFromFile("HIT", mob)),1,1,NULL);
				spin = gtk_spin_button_new(GTK_ADJUSTMENT(HealthBar), 1, 0);
				gtk_signal_connect(HealthBar,"value-changed", G_CALLBACK(HpSet), &SHP);
			
				GtkObject* Initia= gtk_adjustment_new(NuInit+(( StringToInt(GetFromFile("DEX", mob))-10)/2), 0,60,1,1,NULL);
				initiative = gtk_spin_button_new(GTK_ADJUSTMENT(Initia), 1, 0);
				
				gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(hp), (float)SHP/(float)StringToInt(GetFromFile("HIT", mob)));	
				gtk_progress_bar_set_text(GTK_PROGRESS_BAR(hp), HP.c_str());
		
				std::string Stats="AC: ";
				Stats.append(GetFromFile("AC", mob));
				Stats.append(" STR:");
				Stats.append(GetFromFile("STR", mob));
				Stats.append(" DEX:");
				Stats.append(GetFromFile("DEX", mob));
				Stats.append(" CON:");
				Stats.append(GetFromFile("CON", mob));
				Stats.append("\nSP:");
				Stats.append(GetFromFile("SP", mob));
				Stats.append(" INT:");
				Stats.append(GetFromFile("INT", mob));
				Stats.append(" WIS:");
				Stats.append(GetFromFile("WIS", mob));
				Stats.append(" CHA:");
				Stats.append(GetFromFile("CHA", mob));
				Stats.append("\nDMG:");
				Stats.append(GetFromFile("DMG", mob));

				stats=gtk_label_new(Stats.c_str());
	
				gtk_table_attach(GTK_TABLE(table), name, 0, 1, i, i+1, GTK_FILL, GTK_FILL, 0, 0);
				gtk_table_attach(GTK_TABLE(table), image, 0, 1, i+1, i+2, GTK_FILL, GTK_FILL, 0, 0);
				gtk_table_attach(GTK_TABLE(table), hp, 1, 2, i, i+1, GTK_FILL, GTK_FILL, 0, 0);
				gtk_table_attach(GTK_TABLE(table), stats, 1, 2, i+1, i+2, GTK_FILL, GTK_FILL, 0, 0);
				gtk_table_attach(GTK_TABLE(table), spin, 3, 4, i, i+1, GTK_FILL, GTK_FILL, 0, 0);
				gtk_table_attach(GTK_TABLE(table), initiative, 3, 4, i+1, i+2, GTK_FILL, GTK_FILL, 0, 0);
				gtk_table_attach(GTK_TABLE(table), roll, 2, 3, i+1, i+2, GTK_FILL, GTK_FILL, 0, 0);

	}
int main(int argc, char* argv[])
	{
		//Initiates GTK
		gtk_init(&argc, &argv);
		
		//Initialize a window
		GtkWidget* window;
		window=gtk_window_new(GTK_WINDOW_TOPLEVEL);

		GtkWidget* table;
		table=gtk_table_new(2,2,0);	
		const char* Encounter = "TestEncounter";

		for(int i=0; i<StringToInt(GetFromFile("MOBS", Encounter)); i++)
			{
				std::string Name = "NAME";
				std::string Type = "MOB";
				Name.append(std::to_string(i+1));
				Type.append(std::to_string(i+1));
				AddMob(table, i, GetFromFile(Name.c_str(), Encounter).c_str(), GetFromFile(Type.c_str(), Encounter).c_str());
			}
		//Exit event:
		g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit), NULL);

		//Adds table to window;
		gtk_container_add(GTK_CONTAINER(window), table);
	
		//Sets window size:
		gtk_widget_set_size_request(window, 640, 480);
		//Sets Window Name:
		gtk_window_set_title(GTK_WINDOW(window),"Initiative Tracker");
		//Renders:
		gtk_widget_show_all(window);
		//Loops GTK
		gtk_main();
		return 0;
	}
