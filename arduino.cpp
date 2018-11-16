unsigned long signal_len, t1, t2;
int inputPin = 2;
int ledPin = 4;
int ledPin2 = 7;
int ledPin3 = 13;
String code = "";
int flag=0;
int cnt=0;
int arr[200];

void setup()
{
    pinMode(ledPin3,OUTPUT);
    Serial.begin(9600);
    pinMode(inputPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    Serial.print("Inputs for encoding: ");
}

void loop()
{
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3,HIGH);
    delay(50);
    digitalWrite(ledPin3,LOW);
NextDotDash:
    while (digitalRead(inputPin) == HIGH) {}
    t1 = millis();
    digitalWrite(ledPin, HIGH);
    while (digitalRead(inputPin) == LOW) {}
    t2 = millis();
    digitalWrite(ledPin, LOW);
    signal_len = t2 - t1;
    if (signal_len > 50)
    {
        code += readio();
    }
    while ((millis() - t2) < 500)
    {
        if (digitalRead(inputPin) == LOW)
        {
            goto NextDotDash;
        }
    }
    int output,i;
    output=convertor();
    arr[cnt++]=output;
    int coun=11;

    if(cnt==coun)
    {
        Serial.println("\nNRZL: ");
        int f=0;
        for(i=0; i<coun; i++)
        {
            if(arr[i]==0)
            {
                if(f==0)
                {
                    Serial.print("|");
                }
                Serial.print("^");
                f=1;
            }
            else
            {
                if(f==1||i==0)
                {
                    Serial.print("|");
                }
                Serial.print("_");
                f=0;
            }
        }
        Serial.println("|\nNRZI: ");
        int flg=0;
        f=0;
        //Serial.print("|");
        for(i=0; i<coun; i++)
        {
            //Serial.print("|");
            if(arr[i]==1)
            {
                f++;

                if(f%2==1)
                {
                    Serial.print("|");
                    Serial.print("^");
                }
                else
                {
                    Serial.print("|");
                    Serial.print("_");
                }
            }
            else
            {
                if(i==0)
                {
                    Serial.print("|");
                }
                if(f%2==0)
                {
                    Serial.print("_");
                }
                else
                {
                    Serial.print("^");
                }
            }
        }
        Serial.print("|");

        Serial.println("\nUni-Polar: ");
        f=0;
        for(i=0; i<coun; i++)
        {
            if(arr[i]==0)
            {
                if(f==0)
                {
                    Serial.print("|");
                }
                Serial.print("_");
                f=1;
            }
            else
            {
                if(f==1||i==0)
                {
                    Serial.print("|");
                }
                Serial.print("^");
                f=0;
            }
        }
        Serial.print("|");

        Serial.println("\nManchester: ");
        f=0;
        for(i=0; i<coun; i++)
        {
            if(arr[i]==0)
            {
                if(arr[i-1]==0)
                {
                    Serial.print("|");
                }
                Serial.print("`|.");
            }
            else
            {
                if(arr[i-1]==1||i==0)
                {
                    Serial.print("|");
                }
                Serial.print(".|`");
            }
        }
        Serial.println("|");
        //Serial.print("Inputs for encoding: ");
    }
}

char readio()
{
    if (signal_len < 600 && signal_len > 50)
    {
        return '0';
    }
    else if (signal_len > 600)
    {
        return '1';
    }
}
int convertor()
{
    if (code == "0")
    {
        Serial.print("0 ");
        code = "";
        return 0;
    }
    else if (code == "1")
    {
        Serial.print("1 ");
        code = "";
        return 1;
    }
}
