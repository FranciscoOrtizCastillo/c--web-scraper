// scraper.cpp

#include <iostream>
#include "cpr/cpr.h"
#include "libxml/HTMLparser.h"
#include "libxml/xpath.h"
#include <vector>

// define a struct where to store the scraped data
struct NoticiaCard
{
    std::string image;
    std::string url;
    std::string name;
};

int main()
{
    // define the user agent for the GET request
    cpr::Header headers = {{"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36"}};
    // make an HTTP GET request to retrieve the target page
    cpr::Response response = cpr::Get(cpr::Url{"https://www.race.es/"}, headers);
    //std::cout << response.text.c_str() << "\n";

    // parse the HTML document returned by the server
    htmlDocPtr doc = htmlReadMemory(response.text.c_str(), response.text.length(), nullptr, nullptr, HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR);
    
    // define an array to store all retrieved data
    std::vector<NoticiaCard> noticia_cards;
    // set the libxml2 context to the current document
    xmlXPathContextPtr context = xmlXPathNewContext(doc);

    // select all noticias card HTML elements
    // with an XPath selector
    //wpb_single_image
    xmlXPathObjectPtr noticia_card_html_elements = xmlXPathEvalExpression((xmlChar *)"//div[contains(@class, 'vc_gitem-zone-mini')]", context);

    // iterate over the list of noticias card elements
    for (int i = 0; i < noticia_card_html_elements->nodesetval->nodeNr; ++i)
    {
        // get the current element of the loop
        xmlNodePtr noticia_card_html_element = noticia_card_html_elements->nodesetval->nodeTab[i];
        // set the libxml2 context to the current element
        // to limit the XPath selectors to its children
        xmlXPathSetContextNode(noticia_card_html_element, context);

        xmlNodePtr image_html_element = xmlXPathEvalExpression((xmlChar *)".//figure/a/img", context)->nodesetval->nodeTab[0];
        std::string image = std::string(reinterpret_cast<char *>(xmlGetProp(image_html_element, (xmlChar *)"src")));
        //std::cout << image << "\n";
        xmlNodePtr url_html_element = xmlXPathEvalExpression((xmlChar *)".//figure/a", context)->nodesetval->nodeTab[0];
        std::string url = std::string(reinterpret_cast<char *>(xmlGetProp(url_html_element, (xmlChar *)"href")));

        xmlNodePtr name_html_element = xmlXPathEvalExpression((xmlChar *)".//div[contains(@class, 'post-title')]/div/a", context)->nodesetval->nodeTab[0];
        std::string name = std::string(reinterpret_cast<char *>(xmlNodeGetContent(name_html_element)));
        //std::cout << name << "\n";

        // instantiate an NoticiaCard struct with the collected data
        NoticiaCard noticia_card = {image, url, name};
        // add the object with the scraped data to the vector
        noticia_cards.push_back(noticia_card);
    }

    // free up the resource allocated by libxml2
    xmlXPathFreeObject(noticia_card_html_elements);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);

    // initialize the CSV output file
    std::ofstream csv_file("output.csv");
    // write the CSV header
    csv_file << "url,image,name" << std::endl;

    // poupulate the CSV output file
    for (NoticiaCard noticia_card : noticia_cards)
    {
        // transfrom each noticia card record to a CSV record
        csv_file << noticia_card.url << "," << noticia_card.image << "," << noticia_card.name << std::endl;
    }

    // free up the file resources
    csv_file.close();

    return 0;
}