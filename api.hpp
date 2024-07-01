String ApiHost = "http://localhost:3001";

String processResponse(int httpCode, HTTPClient& http)
{
  String payload;
	if (httpCode > 0) {
		Serial.printf("Response code: %d\t", httpCode);

		if (httpCode == 200) {
			payload = http.getString();
			Serial.println(payload);
		}
	}
	else {
		Serial.printf("Request failed, error: %s\n", http.errorToString(httpCode).c_str());
	}
	http.end();
  return payload;
}

void GetEndPointConnection()
{
	HTTPClient http;
  WiFiClient client;
	http.begin(client, ApiHost + "/readings/");
	int httpCode = http.GET();
	processResponse(httpCode, http);
}

void Get(String id) {
  HTTPClient http;
  WiFiClient client;
	http.begin(client, ApiHost + "/readings/" + id);
	int httpCode = http.GET();
	processResponse(httpCode, http);
}

void GetAll()
{
	HTTPClient http;
  WiFiClient client;
	http.begin(client, ApiHost + "/readings/all");
	int httpCode = http.GET();
	processResponse(httpCode, http);
}

String Post(String newData)
{
	HTTPClient http;
  WiFiClient client;
	http.begin(client, ApiHost + "/readings/");
	http.addHeader("Content-Type", "application/json");

	String message = "reading";
	StaticJsonDocument<300> jsonDoc;
	jsonDoc["reading"] = newData;
	serializeJson(jsonDoc, message);

	int httpCode = http.POST(message);
	String response = processResponse(httpCode, http);
  return response;
}

void Put(String id, String newData)
{
	HTTPClient http;
  WiFiClient client;
	http.begin(client, ApiHost + "/readings/" + id);
	http.addHeader("Content-Type", "application/json");

	String message = "";
	StaticJsonDocument<300> jsonDoc;
	jsonDoc["data"] = newData;
	serializeJson(jsonDoc, message);

	int httpCode = http.PUT(message);
	processResponse(httpCode, http);
}

void Patch(String id, String newData)
{
	HTTPClient http;
  WiFiClient client;
	http.begin(client, ApiHost + "/item/" + id);
	http.addHeader("Content-Type", "application/json");

	String message = "";
	StaticJsonDocument<300> jsonDoc;
	jsonDoc["data"] = newData;
	serializeJson(jsonDoc, message);

	int httpCode = http.PATCH(message);
	processResponse(httpCode, http);
}

void DeleteById(String id)
{
	HTTPClient http;
  WiFiClient client;
	http.begin(client, ApiHost + "/readings/" + id);
	int httpCode = http.sendRequest("DELETE");
	processResponse(httpCode, http);
}