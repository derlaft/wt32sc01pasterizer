package main

import (
	"bufio"
	"flag"
	"log"
	"os"
	"os/signal"
	"strconv"
	"strings"
	"syscall"

	"go.bug.st/serial"
)

func main() {

	mode := &serial.Mode{
		BaudRate: 1200,
		DataBits: 8,
		StopBits: 2,
		Parity:   serial.SpaceParity,
	}

	portFile := flag.String("port", "/dev/serial/by-id/usb-Silicon_Labs_CP2102_USB_to_UART_Bridge_Controller_0001-if00-port0", "Serial port to use")
	flag.Parse()
	if !flag.Parsed() {
		flag.Usage()
	}

	log.Println("opening the port")
	port, err := serial.Open(*portFile, mode)
	if err != nil {
		log.Fatal(err)
	}

	go func() {
		sigs := make(chan os.Signal, 1)
		signal.Notify(sigs, syscall.SIGINT, syscall.SIGTERM)
		<-sigs
		log.Println("... exiting")
		port.Close()
	}()

	go func() {
		scanner := bufio.NewScanner(os.Stdin)
		for scanner.Scan() {
			str := scanner.Text()
			for _, sym := range strings.Split(str, " ") {
				d, _ := strconv.ParseInt(sym, 16, 16)
				if d == 0 {
					continue
				}
				err := resp(port, byte(d))
				if err != nil {
					log.Fatal(err)
				}
			}
		}
	}()

	log.Println("starting device loop")
	err = deviceEmulator(port)
	if err != nil {
		log.Fatal(err)
	}
}

func resp(port serial.Port, d byte) error {
	_, err := port.Write([]byte{d})
	if err != nil {
		return err
	}

	log.Printf("<< %x (%c)", d, d)
	return nil
}

func deviceEmulator(port serial.Port) error {
	for {
		var buf [2]byte
		n, err := port.Read(buf[:])
		if err != nil {
			return err
		}

		switch n {
		case 2:
			log.Printf(">> %x (%c) %x (%c)", buf[0], buf[0], buf[1], buf[1])

			// write resp byte 1
			err = resp(port, buf[0])
			if err != nil {
				return err
			}

			// write resp byte 2
			err = resp(port, buf[1])
			if err != nil {
				return err
			}
		case 1:
			log.Printf(">> %x (%c)", buf[0], buf[0])

			// write resp byte 1
			err = resp(port, buf[0])
			if err != nil {
				return err
			}

		case 0:
			log.Println("EOF")
			return nil
		}

		_, err = port.Write(buf[:n])
		if err != nil {
			return err
		}

	}
}
