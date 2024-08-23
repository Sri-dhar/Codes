#include <bits/stdc++.h>
using namespace std;

#define FRAME_SIZE 20
#define FLAG_SEQUENCE "1010"
#define ESC_SEQUENCE "1101"

string StringToBitStream(string s)
{
    string res = "";
    for (auto x : s)
    {
        res += bitset<8>(x).to_string();
    }
    return res;
}

string BitStreamToString(string b)
{
    string res = "";
    for (size_t i = 0; i < b.size(); i += 8)
    {
        res += char(bitset<8>(b.substr(i, 8)).to_ulong());
    }
    return res;
}

string processForSequence(string frame)
{
    string res = "";
    string esc = ESC_SEQUENCE;
    string flag = FLAG_SEQUENCE;

    for (int i = 0; i < frame.size(); i++)
    {
        if (frame.substr(i, flag.size()) == flag)
        {
            res += esc;
            res += flag;
            i += flag.size() - 1;
        }
        else
        {
            res += frame[i];
        }
    }
    return res;
}

string processForDeSequence(string frame)
{
    string res = "";
    size_t i = 0;
    string esc = ESC_SEQUENCE;
    string flag = FLAG_SEQUENCE;

    while (i < frame.size())
    {
        if (frame.substr(i, esc.size()) == esc && frame.substr(i + esc.size(), flag.size()) == flag)
        {
            i += esc.size();  
            res += flag;
i += flag.size();           
        }
        else
        {
            res += frame[i++];
        }
    }
    return res;
}


vector<string> bitStuffing(vector<string> frames)
{
    vector<string> stuffedFrames;
    for (const auto &frame : frames)
    {
        string stuffedFrame = "";
        stuffedFrame.append(FLAG_SEQUENCE);
        stuffedFrame.append(processForSequence(frame));
        stuffedFrame.append(FLAG_SEQUENCE);
        stuffedFrames.push_back(stuffedFrame);
    }
    return stuffedFrames;
}

vector<string> bitUnstuffing(vector<string> frames)
{
    vector<string> unstuffedFrames;
    for (const auto &frame : frames)
    {
        string unstuffedFrame = "";
        for (int i = string(FLAG_SEQUENCE).length(); i < frame.size() - string(FLAG_SEQUENCE).length(); i++)
        {
            unstuffedFrame += frame[i];
        }
        unstuffedFrame = processForDeSequence(unstuffedFrame);
        unstuffedFrames.push_back(unstuffedFrame);
    }
    return unstuffedFrames;
}

int main()
{
    string data = "";
    cout << "Enter the data to send : ";
    getline(cin, data);
    cout << "\n";

    cout << "ESC_SEQUENCE : " << ESC_SEQUENCE << "\n";
    cout << "FLAG_SEQUENCE : " << FLAG_SEQUENCE << "\n\n";

    string bitsStream = StringToBitStream(data);
    vector<string> frames;
    for (int i = 0; i < bitsStream.size(); i += FRAME_SIZE)
    {
        string tempFrame = bitsStream.substr(i, min(FRAME_SIZE, (int)bitsStream.size() - i));
        frames.push_back(tempFrame);
    }

    int originalBitStreamLength = bitsStream.size();

    if (!frames.empty() && frames.back().size() < FRAME_SIZE)
    {
        frames.back().append(FRAME_SIZE - frames.back().size(), '0');
    }

    cout << "Frames are :\n";
    for (int i = 0; i < frames.size(); i++)
    {
        cout << "Frame " << i << " " << frames[i] << "\n";
    }
    cout << "\n";

    auto stuffedFrames = bitStuffing(frames);
    for (int i = 0; i < stuffedFrames.size(); i++)
    {
        cout << "Stuffed Frame " << i << " : " << stuffedFrames[i] << "\n";
    }
    cout << "\n";
    cout << "DATA is sent over the network\n\n";

    auto unstuffedFrames = bitUnstuffing(stuffedFrames);
    for (int i = 0; i < unstuffedFrames.size(); i++)
    {
        cout << "Unstuffed Frame " << i << " : " << unstuffedFrames[i] << "\n";
    }
    cout << "\n";

    string joinedFrames = "";
    for (const auto &frame : unstuffedFrames)
    {
        joinedFrames.append(frame);
    }

    joinedFrames = joinedFrames.substr(0, originalBitStreamLength);

    cout << "Data after Unstuffing : " << BitStreamToString(joinedFrames) << "\n";

    return 0;
}
