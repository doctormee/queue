# Система Электронной Очереди
0. Используемые термины

    **Специалист** — внесённый в Систему человек, оказывающий одну или несколько услуг 
    
    **Пользователь** — конечный получатель услуги
1. Порядок установки

    Скачайте все файлы и поместите их в директорию, в которой планируется размещение готовой системы. Затем в терминале, находясь в этой папке, выполните следующую команду (без кавычек) "make build". В случае успешного завершения работы make, в папке будут располагаться три исполняемых файла: server, customer и admin. 
2. Спецификации системы

    1. Пользователи и приоритет
    
        При входе в систему, пользователь обязан, после выбора в меню соответствующей услуги, ввести все свои персональные данные, которые будут запрашиваться: Фамилию, Имя, Возраст, Вес, Рост и Пол. Установка администратором правил определения приоритета возможна только путём сравнения значений полей Возраст, Вес, Рост и Пол с целым неотрицательным числом. О том, как работать в консоли администратора, читайте пункт 3.3.
    2. Сохранение состояния системы
    
        Система способна сохранять и восстанавливать в дальнейшем одно специфическое состояние (о том, как это сделать, читайте пункт 3.4). При этом сохраняется информация о специалистах, оказываемых ими услугах и приоритетах, но не состояние очереди и база пользователей.
3. Взаимодействие с системой

    1. Начало работы с системой
    
        Процесс Server следует запускать до начала работы, это серверная часть системы. Customer — клиентская часть, через неё осуществляется взаимодействие с системой отдельных пользователей. Admin — консоль администратора системы. Для корректного завершения работы системы следует в консоли администратора выбрать пункт "Завершить работу системы". Ручное прерывание работы процесса server может привести к непредсказуемым последствиям. 
    2. Пользовательский интерфейс
    
        Интерфейс пользователя представляет из себя текстовое меню, состоящее из пронумерованных пунктов. Для выбора конкретного пункта пользователь должен ввести в консоль его номер без точки и нажать клавишу enter (return). Когда у пользователя запрашиваются данные, ему следует ввести одну строку и нажать enter (return) для полей Имя и Фамилия, ввести целое положительное число, не превышающее 32767, и нажать enter (return) для полей Возраст, Вес, Рост, ввести заглавную латинскую букву M или F и нажать enter (return) для поля Пол. 
    3. Консоль администратора
    
        Консоль администратора представляет из себя текстовое меню, аналогичное пользовательскому (см. пункт 3.2), в котором присутствуют соответствующие пункты. Кроме того, при выборе пункта "добавить правило определения приоритета", администратор должен ввести команду следующего вида (в скобках дан пример корректной команды):
        
            param1 sign1 value1 param2 sign2 value2 (age > 10 height < 100)
        или
        
            param1 sign1 value1 all (age < 90 all)
        или
        
            all param2 sign2 value2
        где:
        
            param1, param2 — одно из следующих слов: age, height, weight, gender 
            sign1, sign2 — один из следующих знаков: >, >=, <, <=, ==, !=, или, в случае если param1 (param2) это слово gender – ==, !=
            value1, value2 — целое неотрицательное число, не превыщающее 32767, или, в случае если param1 (param2) это слово gender – букву 'M' или 'F'. 
        После выполнения такой команды все пользователи, удовлетворяющие условию param1 sign1 value1 (например, age > 20) будут считаться приоритетнее, чем пользователи, удовлетворяющие условию param2 sign2 value2. Слово all, написанное вместо тройки param sign value обозначает всех пользователей.
    4. Сохранение состояния системы и загрузка сохранённой конфигурации
    
        Для сохранения состояния системы следует выбрать соответствующий пункт в консоли администратора. После повторного запуска системы для восстановления данных требуется выбрать пункт "Загрузить конфигурацию системы".