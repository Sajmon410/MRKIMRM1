# 1. Задатак

QT развојно окружење – Publish

Subscribe Server – topic based

Реализација једноставног модела послужиоца publish

subscribe асоцијација. Послужилац спада у класу ,,topic

based’’ послужилаца. Реализовати и пример коришћења

послужиоца. Задатак реализовати коришењем QT развојног

окружења.

# 2. Концепт решења

Решење датог проблема се огледа у реализацији аутомата ослањајући се на постојеће библиотеке и фајлове које QT нуди.

QT има библиотеке QTcpSocket и QTcpServer које омогућавају лаку и једноставну комуникацију између клијената и сервера помоћу побудних сигнала који се емитују у датим околностима као што су: QTcpServer::newConnection(), QTcpSocket::readyRead(), QTcpSocket::connected(), QTcpSocket::disconnected()…

Дати сигнали су повезани за објекат што их позива и морају бити спојени са одговарајућим слотовима које ми сами куцамо и одређујемо функционалности које се извршавају приликом дате побуде. Тако рецимо у нашем случају сервер за сваку нову конекцију што „чује“ позива функцију newConnection() која ће направити податке о клијенту и сокету у листу клијената датог сервера.

Помоћу тих побудних сигнала и слотова што одређују процедуру и понашање приликом побуде ћемо реализовати комуникацију клијента и сервера. Клијенти ће имати своју класу (User) у којој ће бити специфиран сокет који се користи, тема коју прате и мод (read / write) који су бирали за ту тему.

# 3. Опис решења

Опис решења најлакше може бити приказан SDL и MSC дијаграмима. Задатак је реализован помоћу сервер и клијент аутомата, који као што је приказано на дијаграмима на слици 1 и слици 2 порукама између клијената и сервера побуђују промену стања.

Поруке које опсужиоц прима од стране клијента се парсирају интерном логиком, а након тога неке чувају у листи клијената која садржи информације о теми шта клијент жели да прати и моду клијента тачније да ли хоће да чита новости тражене теме или хоће да сам пише новости за њу.

Након покретања опслужиоца, клијенти могу слободно да приступају истом и помоћу дефинисаних шаблона комуницирају и очекују одговор у зависности од поруке.

· Прво се шаље ‘’read’’ или ‘’write’’ , сервер треба да одреди мод клијента

· Потом клијент добија поруку од сервера са упитом да напише коју тему жели да прати. Ту клијент специфира коју тему жели да прати.

· У зависности од бираног мода клијет сада почиње другачије да се понаша.

· Клијенти у ’write’’ моду ће бити у могућности континуално да пишу новости на задату тему, а клијенти у ’read’’ моду само примају новости на основу тему коју прате.
# 4. Тестирање

Тестирање није аутоматски вршено, већ мануелним покретањем 3 или више клијената, где сваки од њих серверу шаље по неку од понуђених опција и сервер исписује податке о послатим порукама и тренутно конектованим клијентима.

Теме на које је додаван садржај успешно се приказују на сваком од пријављених корисника, а они који нису пријављени не добијају паткете ван своје теме.
