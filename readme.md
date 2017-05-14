# Система Электронной Очереди (прототип)
0. Используемые термины

    **Клиент** — пользователь системы 
    
    **Специалист** — внесённый в Систему человек, оказывающий одну или несколько услуг 
    
    **Пользователь** — конечный получатель услуги
    
    **Правило** — пара логических выражений (условий)
1. Порядок установки

    Скачайте все файлы и поместите их в директорию, в которой планируется размещение готовой системы. Затем в терминале, находясь в этой папке, выполните следующую команду: `make build`
    
    В случае успешного завершения работы make, в папке будет располагаться исполняемый файл priority_queue. 
    
    Для запуска тестов запустите следующую команду: `make gtest && make test`
    
    Для просмотра покрытия после запуска тестов запустите следующую команду: `make cov`
    
    Для того, чтобы сгенерировать исполняемый файл и запустить тесты, запустите следующую команду: `make`
    
2. Спецификации системы

    1. Пользователи и приоритет
    
        При входе в систему, пользователь обязан, после выбора в меню соответствующей услуги, ввести все свои персональные данные, которые будут запрашиваться: Фамилию, Имя, Возраст, Вес, Рост и Пол. Установка администратором правил определения приоритета возможна только путём сравнения значений полей Возраст, Вес, Рост и Пол с целым неотрицательным числом. О том, как работать в консоли администратора, читайте пункт 3.3.
        Приоритет пользователя определяется как число, высчитываемое по следующей формуле: для каждого существующего правила определения приоритета, если текущий пользователь удовлетворяет первому условию, его приоритет увеличивается на число других пользователей, стоящих в этой очереди, удовлетворяющих второму логическому условию. 
    2. Сохранение состояния системы
    
        Система способна сохранять и восстанавливать в дальнейшем одно специфическое состояние (о том, как это сделать, читайте пункт 3.4). При этом сохраняется информация о специалистах, оказываемых ими услугах и правилах определения приоритета, но не состояние очереди и база пользователей.
3. Взаимодействие с системой

    1. Начало работы с системой
    
        Процесс System представляет собой всю систему. После запуска этого процесса клиент должен выбрать в появившемся меню один из пунктов: войти как существующий пользователь (по Идентификатору), как новый пользователь или как администратор
    2. Пользовательский интерфейс
    
        Интерфейс пользователя представляет из себя текстовое меню, состоящее из пронумерованных пунктов. Для выбора конкретного пункта пользователь должен ввести в консоль его номер без точки и нажать клавишу enter (return). Когда у пользователя запрашиваются данные, ему следует ввести одну строку и нажать enter (return) для полей Имя и Фамилия, ввести целое положительное число, помещающееся в тип int, и нажать enter (return) для полей Возраст, Вес, Рост, ввести заглавную латинскую букву M или F и нажать enter (return) для поля Пол. 
    3. Консоль администратора
    
        Консоль администратора представляет из себя текстовое меню, аналогичное пользовательскому (см. пункт 3.2), в котором присутствуют соответствующие пункты. Кроме того, при выборе пункта "добавить правило определения приоритета", администратор должен по приглашению системы написать последовательно два логических выражения на языке логических выражений. (Грамматику этого языка см. пункт 4)
    4. Сохранение состояния системы и загрузка сохранённой конфигурации
    
        Для сохранения состояния системы следует выбрать соответствующий пункт в консоли администратора. После повторного запуска системы для восстановления данных требуется выбрать пункт "Загрузить конфигурацию системы".
4. Язык логических выражений
    
    Грамматика языка логических выражений имеет следующий вид (здесь {выражение} означает выражение, повторённое 0 и более раз, слово в одинарных кавычках — терминальный символ (последовательность терминальных символов), слово заглавными буквами — нетерминальный символ, выражение a..z — один любой терминальный символ из диапазона [a, z])
    
     IMP = DISJ {'->' IMP}
     
     DISJ = CONJ {'|' DISJ} 
     
     CONJ = NEG {'&' CONJ}
     
     NEG = {'!'}PAR
     
     PAR = '('DISJ')' | TERM
     
     TERM = FIELD SIGN VALUE | 'gender' EQNOTEQ GENVALUE| ALL
     
     FIELD = 'height' | 'weight' | 'age'
     
     SIGN = '>' | '>=' | '<' | '<=' | EQNOTEQ
     
     VALUE = {'0'}{1..9} 
     
     GENVALUE = 'M' | 'F'
     
     EQNOTEQ = '=' | '!='
     
     Кроме того, целое число, порождаемое нетерминалом VALUE, должно вмещаться целиком в тип int и быть неотрицательным