#include "pebble.h"

float timer_delay=1; /* Создаем переменную для с временем для таймера */
Window *window; /* Создаем указатель на окно */
TextLayer *text_layer;  /* создаем  указатель на текстовый слой */
static BitmapLayer *image_layer; /* создаем  указатель на графический слой */
static GBitmap *image; /* создаем  указатель на изображение в памяти */
bool first_time=true; /* создаем флаг первого запуска */
int lang=1; /* создаем переменную языка: eng-1, rus-2, ge-3 */

static const char* messages_en[] = {"In the bathroom","In the kitchen","On the floor","On the bed","In the toilet","In the corridor","In the friends house","On the balcony","In the closet","In the elevator","In the weather","In the car","In water","In a public toilet","When burning candles","In the bedroom","In the living room","In the fitting room","In the cinema","During video recording","On the beach",}; /* Создаем массив ответов */
static const char* messages_ru[] = {"В ванной","На кухне","На полу","На кровати","В туалете","В коридоре","В гостях","На балконе","В шкафу","В лифте","На улице","В машине","В воде","В общественном туалете","При свечах","В спальне","В гостиной","В примерочной кабинке","В кинотеатре","Перед камерой","На пляже",}; /* Создаем массив ответов */
static const char* messages_ge[] = {"Im Badezimmer","In der Küche","Auf dem Boden","Im Bett","Auf der Toilette","Im Korridor","Im Haus des Freundes","Auf dem Balkon","Auf dem Klo","Im Fahrstuhl","Auf dem Tisch","Im Auto","Im Wasser","Auf einer öffentlichen Toilette","Bei Kerzenschein","Im Schlafzimmer","Im Wohnzimmer","In der Umkleidekabine","Im Kino","Bei laufender Kamera","Am Strand",}; /* German Locations */
static const char* message_hello_ru= "Sex Roulette \n Нажми на любую кнопку, чтобы выбрать позу и место -->";
static const char* message_hello_en= "Sex Roulette \n \n Click on any button to select a random pose and place \n ---------------->";
static const char* message_hello_ge= "Sex Roulette \n Drücke einen beliebigen Knopf für Ort und Stellung -->";

static const uint32_t images[] = {RESOURCE_ID_POSE_1,RESOURCE_ID_POSE_2,RESOURCE_ID_POSE_3,RESOURCE_ID_POSE_4,RESOURCE_ID_POSE_5,RESOURCE_ID_POSE_6,RESOURCE_ID_POSE_7,RESOURCE_ID_POSE_8,RESOURCE_ID_POSE_9,RESOURCE_ID_POSE_10,RESOURCE_ID_POSE_11,RESOURCE_ID_POSE_12,RESOURCE_ID_POSE_13,RESOURCE_ID_POSE_14,RESOURCE_ID_POSE_15,RESOURCE_ID_POSE_16,RESOURCE_ID_POSE_17,RESOURCE_ID_POSE_18,RESOURCE_ID_POSE_19,RESOURCE_ID_POSE_20,RESOURCE_ID_POSE_21,RESOURCE_ID_POSE_22,RESOURCE_ID_POSE_23,RESOURCE_ID_POSE_24,RESOURCE_ID_POSE_25,RESOURCE_ID_POSE_26,RESOURCE_ID_POSE_27,RESOURCE_ID_POSE_28,RESOURCE_ID_POSE_29,RESOURCE_ID_POSE_30,RESOURCE_ID_POSE_31,RESOURCE_ID_POSE_32,}; /* Создаем массив идентификаторов ресурсов */
 

void timer_call() /* эта функция вызывается при срабатывании таймера */
{
    if (first_time == false) /* если запускается не в первый раз... */
      {
        bitmap_layer_destroy(image_layer); /* ...то удаляем старый слой... */
        gbitmap_destroy(image); /* ...и очищаем память от предыдущей картинки */
      }
    first_time = false; /* сбрасываем флаг первого запуска */

    image_layer = bitmap_layer_create(GRect(0 , 0, 144, 144)); /* создаем графический массив, указываем размер и координаты */
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(image_layer)); /* подключаем графический слой к основному в качестве дочернего */
    bitmap_layer_set_compositing_mode(image_layer, GCompOpAssignInverted); /* настраиваем параметр наложения */

    image = gbitmap_create_with_resource(images[rand() % 31]); /* загружаем в память случайную картинку из подключенных ресурсов */
    bitmap_layer_set_bitmap(image_layer, image); /* выводим загруженную картинку в слой */
	
	switch (lang) 
	{
		case 1:  text_layer_set_text(text_layer, messages_en[rand() % 20]); /* выводим случайное сообщение */
		break;
		case 2:  text_layer_set_text(text_layer, messages_ru[rand() % 20]); /* выводим случайное сообщение */
		break;
		case 3:  text_layer_set_text(text_layer, messages_ge[rand() % 20]); /* выводим случайное сообщение */
		break;
	}
    
    if (timer_delay < 300*100 ) /* если задержка еще не достигла 300мс... */
    {
        timer_delay=timer_delay/0.7; /* ...увеличиваем задержку... */
        app_timer_register(timer_delay/100, timer_call, NULL); /* ...и взводим таймер заново */
    }
    else /* если задержка уже больше 300мс... */
    {
        timer_delay=1; /* сбрасываем таймер на начало и выходим - сообщение и картинку мы же уже показали */
        light_enable_interaction(); /* включаем подсветку */
    }
}

void config_text_layer(int16_t x,int16_t y,int16_t h,int16_t w, const char *font_key)  /* для исключения дублирования кода, создали функцию, которая занимается инициализаций и настройкой текстового массива*/
{
    text_layer = text_layer_create(GRect(x, y, h, w)); /* создаем текстовый массив, указываем размер и координаты */
    text_layer_set_text_color(text_layer, GColorWhite);  /* устанавливаем цвет текста */
    text_layer_set_background_color(text_layer, GColorClear);  /* устанавливаем цвет фона */
    text_layer_set_font(text_layer, fonts_get_system_font(font_key)); /* устанавливаем шрифт */
    text_layer_set_text_alignment(text_layer, GTextAlignmentCenter); /* устанавливаем выравнивание по центру */
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));  /* подключаем текстовый слой к основному в качестве дочернего */
}

void click(ClickRecognizerRef recognizer, void *context)  /* функция, срабатывающая при клике на кнопки */
{
  if (first_time == true) /* если программа запускается в первый раз... */
  {
    text_layer_destroy(text_layer); /* ... то очищаем и удаляем приветствия... */
    config_text_layer(0, 146, 144, 168-146, FONT_KEY_GOTHIC_18); /* ... и создаем новый слой сообщений с другими координатами и шрифтом */
  }
    timer_call(); /* взводим таймер для быстрой смены сообщений */
}

void lang_change(ClickRecognizerRef recognizer, void *context)  /* функция изменения языка */
{
	lang++;
	if (lang >= 4)
	{
		lang = 1;
	}
	click(NULL, NULL);
}

void WindowsClickConfigProvider(void *context)  /* функция, внутри которой должны находиться подписки на кнопки */
{
    window_single_click_subscribe(BUTTON_ID_UP, click); /* при нажатии на верхнюю кнопку запустить click */
    window_single_click_subscribe(BUTTON_ID_SELECT, click); 
    window_single_click_subscribe(BUTTON_ID_DOWN, click);
	window_long_click_subscribe(BUTTON_ID_SELECT, 1000, lang_change, NULL);
}

int main(void)
{
	if (persist_exists(1))
	{
	lang = persist_read_int(1);
	}
	else
	{
	persist_write_int(1, 1);
	lang = 4;
	}
    window = window_create();  /* Инициализируем окно */
    window_set_background_color(window, GColorBlack); /* устанавливаем фоновый цвет */
    window_set_fullscreen(window, true); /* включаем полный экран */
    window_stack_push(window, true);  /* открываем окно */
    srand(time(NULL)); /* инициализируем генератор случайных чисел текущем временем */
    window_set_click_config_provider(window, WindowsClickConfigProvider); /* определяем функцию, в которой будут находиться подписки на кнопки */
    config_text_layer(0, 10, 144, 168, FONT_KEY_GOTHIC_24); /* настраиваем создание текстового слоя с приветственным сообщением */

	switch (lang) 
	{
		case 1:  text_layer_set_text(text_layer, message_hello_en);  /* показываем сообщение при запуске */
		break;
		case 2:  text_layer_set_text(text_layer, message_hello_ru);  /* показываем сообщение при запуске */
		break;
		case 3:  text_layer_set_text(text_layer, message_hello_ge);  /* показываем сообщение при запуске */
		break;
		case 4:  text_layer_set_text(text_layer, "Sex Roulette \nLong press Select\nto switch lang: \n EN, RUS, GE \n Or click any button");   /* показываем сообщение при запуске */
		lang = 1;
		break;
	}

    app_event_loop();  /* ждем событий */
	persist_write_int(1, lang);
    text_layer_destroy(text_layer); /* уничтожаем текстовый слой, освобождаем ресурсы */
    window_destroy(window);  /* уничтожаем главное окно, освобождаем ресурсы */
    bitmap_layer_destroy(image_layer); /* уничтожаем графический слой, освобождаем ресурсы */
    if (first_time == false) /* если мы выходим после запуска рисования... */
    {
    gbitmap_destroy(image); /* то уничтожаем массив с графикой, освобождаем ресурсы, иначе - не уничтожаем, т.к. он еще не создан */
    }
}