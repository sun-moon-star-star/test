package main

import (
	"fmt"
	"math/rand"
	"strings"
	"time"
)

// Data following schema
type Data struct {
	id        int32
	name      string
	address   string
	continent string
}

// GetRandomCSV like 21,axxxxxxxxx,12 abc dfsf LdUE,Asia
func GetRandomCSV() string {
	data := getRandomData()
	return generateCSV(data)
}

func generateCSV(data Data) string {
	var builder strings.Builder
	id := fmt.Sprintf("%d", data.id)
	builder.WriteString(id)
	builder.WriteString(",")
	builder.WriteString(data.name)
	builder.WriteString(",")
	builder.WriteString(data.address)
	builder.WriteString(",")
	builder.WriteString(data.continent)
	return builder.String()
}

func getRandomData() Data {
	id := rand.Int31()
	name := getRandomName()
	address := getRandomAddress()
	continent := getRandomContinent()
	return Data{id, name, address, continent}
}

func getRandomName() string {
	minLen, maxLen := 10, 15
	str := "abcdefghijklmnopqrstuvwxyz"
	return getRandomString(minLen, maxLen, str)
}

func getRandomAddress() string {
	minLen, maxLen := 15, 20
	str := "ABCDEFGHIJKLMNOPQRSRUVWXYZabcdefghijklmnopqrstuvwxyz 1234567890"
	return getRandomString(minLen, maxLen, str)
}

func getRandomContinent() string {
	allContinent := []string{"North America", "Asia", "South America", "Europe", "Africa", "Australia"}
	idx := rand.Intn(len(allContinent))
	return allContinent[idx]
}

func getRandomString(minLen int, maxLen int, str string) string {
	bytes := []byte(str)
	result := []byte{}
	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	length := rand.Intn(maxLen-minLen) + minLen

	for i := 0; i < length; i++ {
		result = append(result, bytes[r.Intn(len(bytes))])
	}
	return string(result)
}

func main() {
	fmt.Println(GetRandomCSV())
}
