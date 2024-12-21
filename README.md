1. Zadatak

QT развојно окружење – Publish

Subscribe Server – topic based

Реализација једноставног модела послужиоца publish

subscribe асоцијација. Послужилац спада у класу ,,topic

based’’ послужилаца. Реализовати и пример коришћења

послужиоца. Задатак реализовати коришењем QT развојног

окружења.
2. Koncept rešenja

Решење датог проблема се огледа у реализацији аутомата ослањајући се на постојеће библиотеке и фајлове које QT нуди.

QT има библиотеке QTcpSocket и QTcpServer које омогућавају лаку и једноставну комуникацију између клијената и сервера помоћу побудних сигнала који се емитују у датим околностима као што су: QTcpServer::newConnection(), QTcpSocket::readyRead(), QTcpSocket::connected(), QTcpSocket::disconnected()…

Дати сигнали су повезани за објекат што их позива и морају бити спојени са одговарајућим слотовима које ми сами куцамо и одређујемо функционалности које се извршавају приликом дате побуде. Тако рецимо у нашем случају сервер за сваку нову конекцију што „чује“ позива функцију newConnection() која ће направити податке о клијенту и сокету у листу клијената датог сервера.

Помоћу тих побудних сигнала и слотова што одређују процедуру и понашање приликом побуде ћемо реализовати комуникацију клијента и сервера. Клијенти ће имати своју класу (User) у којој ће бити специфиран сокет који се користи, тема коју прате и мод (read / write) који су бирали за ту тему.
2. Koncept rešenja

Решење датог проблема се огледа у реализацији аутомата ослањајући се на постојеће библиотеке и фајлове које QT нуди.

QT има библиотеке QTcpSocket и QTcpServer које омогућавају лаку и једноставну комуникацију између клијената и сервера помоћу побудних сигнала који се емитују у датим околностима као што су: QTcpServer::newConnection(), QTcpSocket::readyRead(), QTcpSocket::connected(), QTcpSocket::disconnected()…

Дати сигнали су повезани за објекат што их позива и морају бити спојени са одговарајућим слотовима које ми сами куцамо и одређујемо функционалности које се извршавају приликом дате побуде. Тако рецимо у нашем случају сервер за сваку нову конекцију што „чује“ позива функцију newConnection() која ће направити податке о клијенту и сокету у листу клијената датог сервера.

Помоћу тих побудних сигнала и слотова што одређују процедуру и понашање приликом побуде ћемо реализовати комуникацију клијента и сервера. Клијенти ће имати своју класу (User) у којој ће бити специфиран сокет који се користи, тема коју прате и мод (read / write) који су бирали за ту тему.
4. Testiranje

Тестирање није аутоматски вршено, већ мануелним покретањем 3 или више клијената, где сваки од њих серверу шаље по неку од понуђених опција и сервер исписује податке о послатим порукама и тренутно конектованим клијентима.

Теме на које је додаван садржај успешно се приказују на сваком од пријављених корисника, а они који нису пријављени не добијају паткете ван своје теме.
