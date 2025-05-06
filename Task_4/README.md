#### Версия NS: ns-allinone-3.44
#### Язык: C++

# Содержание
* [Тестовое задание](#task)
* [Настройка NS-3](#settings)
* [Использование кода](#usage)
* [Описание кода](#description)
* [Результат](#result)
* [Список литературы](#resource)

<a name=“task”><h2>Тестовое задание</h2></a>
<details><summary>Задание</summary>

* Установить NS-3 и скомпилировать.
* С помощью документации NS-3 сделать минимальный LTE сценарий:

    * Есть eNB и два абонента.
    * Траффик Full Buffer (пакеты идут в обе стороны бесконечно).
    * В LTE модуле сконфигурирован планировщик пакетов pf-ff-mac-scheduler.
    * В LTE модуле сконфигурирован вывод ключевых характеристик с Rlc и MAC уровня.
  
* Запустить сценарий и получить вывод ключевых характеристик.

**Основное задание**
Написать скрипт, который по полученному выводу ключевых характеристик с Rlc уровня 
посчитает Throughput в DL и в UL для каждого пользователя отдельно и выведет его на экран.

</details>

<a name=“settings”><h2>Настройка NS-3</h2></a>
<details><summary> Установка NS-3</summary>
  
* Скачать архив: https://www.nsnam.org/releases/latest
* Распаковать архив в удобную вам папку.
```Shell
tar xjf ns-allinone-3.44.tar.bz2
```
* Перейти в место распаковки
```Shell
cd ns-allinone-3.44/ns-3.44
```

</details>

<details><summary>Компиляция NS-3</summary>
  
* Чтобы настроить ns-3 с включенными примерами и тестами,
запустите следующую команду в главном каталоге ns-3
```Shell
./ns3 configure --enable-examples --enable-tests
```
* Затем создайте ns-3, выполнив следующую команду:
```Shell
./ns3 build
```
</details>

<a name="usage"><h2>Использование кода</h2></a>
<details><summary>Пример использования кода</summary>

* Файл Scenario.cc вставить в ns-3.44/scratch
* В папке ns-3.41 в терминале ввести:

```Shell
./ns3 run Scenario.cc
```

* После этого в папке ns-3.41 появятся следующие файлы:
    * DlMacStats.txt
    * DlRlcStats.txt
    * UlMacStats.txt
    * UlRlcStats.txt



</details>

<a name="description"><h2>Описание кода</h2></a>

*За основу были взяты части [кода из документации](https://www.nsnam.org/docs/models/html/lte-user.html#basic-simulation-program)*

### Конфигурация модели
```cpp
uint16_t numNodePairs = 2;
Time simTime = Seconds(10.0);
bool epc = true;
bool disableDl = false;
bool disableUl = false;
```
Этот код устанавливает параметры модели, такие как количество пар узлов, время симуляции, наличие EPC и возможность отключения передачи данных в направлении DL и UL.

### Настройка атрибутов по умолчанию
```cpp
Config::SetDefault("ns3::UdpClient::Interval", TimeValue(MilliSeconds(1)));
Config::SetDefault("ns3::UdpClient::MaxPackets", UintegerValue(1000000));
Config::SetDefault("ns3::LteRlcUm::MaxTxBufferSize", UintegerValue(10 * 1024));
```
Этот код устанавливает некоторые атрибуты по умолчанию для компонентов, таких как UdpClient и LteRlcUm.

### Создание сети LTE
```cpp
Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();
Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper>();
lteHelper->SetEpcHelper(epcHelper);
lteHelper->SetSchedulerType("ns3::PfFfMacScheduler");
```
Этот код создает объекты LteHelper и PointToPointEpcHelper для управления LTE сетью и эмуляции EPC.

### Создание узлов и установка соединений
```cpp
NodeContainer remoteHostContainer;
remoteHostContainer.Create(1);
NodeContainer enbNodes;
NodeContainer ueNodes;
```
Этот код создает контейнеры узлов для удаленного хоста, eNB и UE.

### Установка мобильности и сетевых устройств
```cpp
MobilityHelper mobility;
mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
mobility.Install(enbNodes);
mobility.Install(ueNodes);
NetDeviceContainer enbDevs;
NetDeviceContainer ueDevs;
enbDevs = lteHelper->InstallEnbDevice(enbNodes);
ueDevs = lteHelper->InstallUeDevice(ueNodes);
```
Этот код устанавливает модель мобильности и сетевые устройства для узлов eNB и UE.

### Настройка IP адресов и маршрутизации
```cpp
Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign(internetDevices);
Ipv4InterfaceContainer ueIpIface = epcHelper->AssignUeIpv4Address(NetDeviceContainer(ueDevs));
```
Этот код назначает IP адреса и устанавливает маршруты для узлов.

### Установка приложений
```cpp
ApplicationContainer clientApps;
ApplicationContainer serverApps;
```
Этот код создает контейнеры для клиентских и серверных приложений.

### Запуск симуляции
```cpp
serverApps.Start(Seconds(1.0));
clientApps.Start(Seconds(1.0));
Simulator::Stop(simTime);
Simulator::Run();
Simulator::Destroy();
```
Этот код запускает приложения и симуляцию, останавливает ее по истечении времени и завершает работу симулятора.

<a name="result"><h2>Результат</h2></a>
###### Что означают элементы в таблице можно посмотреть [здесь](https://www.nsnam.org/docs/models/html/lte-user.html#simulation-output) (19.2.6 Simulation Output)
* [MAC DL Stats](source/DlMacStats.txt)
* [MAC UL STATS](source/UlMacStats.txt)
* [RLC DL Stats](source/DlRlcStats.txt)
* [RLC UL Stats](source/UlRlcStats.txt)

<a name="resource"><h2>Список литературы</h2></a>

* [Установка и сборка NS-3](https://www.nsnam.org/docs/release/3.41/tutorial/ns-3-tutorial.pdf)
* [LTE для NS-3](https://www.nsnam.org/docs/models/html/lte.html)
* [Реализация full buffer](https://www.nsnam.org/docs/release/3.17/doxygen/lena-dual-stripe_8cc.html) взята из файла lena-dual-stripe
