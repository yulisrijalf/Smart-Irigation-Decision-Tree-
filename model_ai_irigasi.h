#ifndef MODEL_AI_IRIGASI_H
#define MODEL_AI_IRIGASI_H

int prediksi_penyiraman(float Soil_Moisture, float Temperature, float Air_Humidity) {
    if (Soil_Moisture <= 59.50) {
        if (Temperature <= 10.50) {
            if (Soil_Moisture <= 20.50) {
                if (Temperature <= 1.50) {
                    if (Air_Humidity <= 54.50) {
                        if (Air_Humidity <= 52.50) {
                            if (Soil_Moisture <= 19.50) {
                                if (Air_Humidity <= 24.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Air_Humidity <= 46.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Temperature <= 0.50) {
                                if (Air_Humidity <= 53.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Soil_Moisture <= 2.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    } else {
                        if (Temperature <= 0.50) {
                            if (Soil_Moisture <= 6.50) {
                                if (Air_Humidity <= 56.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Soil_Moisture <= 9.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            }
                        } else {
                            if (Air_Humidity <= 65.50) {
                                if (Soil_Moisture <= 15.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Soil_Moisture <= 9.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    }
                } else {
                    if (Temperature <= 7.50) {
                        if (Air_Humidity <= 54.50) {
                            if (Soil_Moisture <= 7.50) {
                                if (Temperature <= 6.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Air_Humidity <= 42.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Soil_Moisture <= 14.50) {
                                if (Air_Humidity <= 56.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Air_Humidity <= 66.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    } else {
                        if (Temperature <= 9.50) {
                            if (Air_Humidity <= 64.50) {
                                if (Air_Humidity <= 31.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Soil_Moisture <= 10.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Air_Humidity <= 47.50) {
                                if (Soil_Moisture <= 16.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Air_Humidity <= 55.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    }
                }
            } else {
                if (Air_Humidity <= 63.50) {
                    if (Temperature <= 1.50) {
                        if (Air_Humidity <= 23.50) {
                            if (Temperature <= 0.50) {
                                return 0;
                            } else {
                                if (Soil_Moisture <= 58.00) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Air_Humidity <= 33.50) {
                                if (Air_Humidity <= 31.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                return 0;
                            }
                        }
                    } else {
                        if (Air_Humidity <= 39.50) {
                            if (Air_Humidity <= 31.50) {
                                if (Temperature <= 2.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Air_Humidity <= 35.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            }
                        } else {
                            if (Temperature <= 7.50) {
                                if (Soil_Moisture <= 49.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Soil_Moisture <= 48.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    }
                } else {
                    if (Temperature <= 2.50) {
                        if (Air_Humidity <= 65.50) {
                            if (Temperature <= 0.50) {
                                return 0;
                            } else {
                                if (Soil_Moisture <= 43.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Temperature <= 0.50) {
                                return 0;
                            } else {
                                if (Soil_Moisture <= 29.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    } else {
                        if (Temperature <= 6.50) {
                            if (Air_Humidity <= 69.50) {
                                if (Air_Humidity <= 67.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Soil_Moisture <= 46.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        } else {
                            if (Soil_Moisture <= 22.50) {
                                if (Temperature <= 8.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Air_Humidity <= 64.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (Temperature <= 25.50) {
                if (Soil_Moisture <= 20.50) {
                    if (Temperature <= 23.50) {
                        if (Temperature <= 15.50) {
                            if (Air_Humidity <= 24.50) {
                                if (Air_Humidity <= 23.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Air_Humidity <= 58.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Temperature <= 17.50) {
                                if (Air_Humidity <= 28.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Soil_Moisture <= 16.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    } else {
                        if (Air_Humidity <= 32.50) {
                            if (Soil_Moisture <= 18.50) {
                                if (Soil_Moisture <= 5.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Soil_Moisture <= 19.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Air_Humidity <= 63.50) {
                                if (Air_Humidity <= 39.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Soil_Moisture <= 6.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    }
                } else {
                    if (Air_Humidity <= 63.50) {
                        if (Air_Humidity <= 51.50) {
                            if (Air_Humidity <= 31.50) {
                                if (Air_Humidity <= 23.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Air_Humidity <= 46.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Temperature <= 20.50) {
                                if (Temperature <= 15.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Air_Humidity <= 55.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    } else {
                        if (Temperature <= 22.50) {
                            if (Temperature <= 20.50) {
                                if (Soil_Moisture <= 53.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Air_Humidity <= 67.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Soil_Moisture <= 28.50) {
                                if (Soil_Moisture <= 23.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Temperature <= 24.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    }
                }
            } else {
                if (Temperature <= 35.50) {
                    if (Soil_Moisture <= 38.50) {
                        if (Air_Humidity <= 58.50) {
                            if (Air_Humidity <= 35.50) {
                                if (Air_Humidity <= 27.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Temperature <= 32.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Air_Humidity <= 63.50) {
                                if (Temperature <= 27.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Soil_Moisture <= 37.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    } else {
                        if (Air_Humidity <= 57.50) {
                            if (Air_Humidity <= 32.50) {
                                if (Air_Humidity <= 27.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Temperature <= 31.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Air_Humidity <= 63.50) {
                                if (Soil_Moisture <= 47.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Soil_Moisture <= 39.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    }
                } else {
                    if (Soil_Moisture <= 9.50) {
                        if (Air_Humidity <= 31.50) {
                            if (Air_Humidity <= 21.50) {
                                if (Soil_Moisture <= 1.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Air_Humidity <= 22.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Temperature <= 43.50) {
                                if (Soil_Moisture <= 8.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Air_Humidity <= 51.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    } else {
                        if (Air_Humidity <= 64.50) {
                            if (Air_Humidity <= 58.50) {
                                if (Air_Humidity <= 21.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Soil_Moisture <= 29.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Temperature <= 40.50) {
                                if (Soil_Moisture <= 13.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Soil_Moisture <= 23.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        if (Temperature <= 21.50) {
            if (Air_Humidity <= 63.50) {
                if (Air_Humidity <= 49.50) {
                    if (Air_Humidity <= 31.50) {
                        if (Soil_Moisture <= 69.50) {
                            if (Temperature <= 10.50) {
                                return 0;
                            } else {
                                if (Soil_Moisture <= 63.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        } else {
                            if (Temperature <= 20.50) {
                                return 0;
                            } else {
                                if (Air_Humidity <= 21.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    } else {
                        if (Temperature <= 12.50) {
                            if (Air_Humidity <= 41.50) {
                                if (Temperature <= 6.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Temperature <= 11.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        } else {
                            if (Air_Humidity <= 45.50) {
                                if (Soil_Moisture <= 69.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Temperature <= 16.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    }
                } else {
                    if (Temperature <= 18.50) {
                        if (Soil_Moisture <= 69.50) {
                            if (Temperature <= 10.50) {
                                return 0;
                            } else {
                                if (Air_Humidity <= 54.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        } else {
                            return 0;
                        }
                    } else {
                        if (Air_Humidity <= 51.50) {
                            if (Soil_Moisture <= 62.50) {
                                return 0;
                            } else {
                                if (Soil_Moisture <= 87.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        } else {
                            if (Soil_Moisture <= 69.50) {
                                if (Air_Humidity <= 60.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Air_Humidity <= 53.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    }
                }
            } else {
                if (Temperature <= 5.50) {
                    if (Air_Humidity <= 65.50) {
                        if (Temperature <= 0.50) {
                            return 0;
                        } else {
                            if (Soil_Moisture <= 70.50) {
                                if (Soil_Moisture <= 67.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Air_Humidity <= 64.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    } else {
                        if (Temperature <= 2.50) {
                            return 0;
                        } else {
                            if (Air_Humidity <= 67.50) {
                                if (Soil_Moisture <= 88.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Temperature <= 4.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    }
                } else {
                    if (Soil_Moisture <= 70.50) {
                        if (Soil_Moisture <= 64.50) {
                            if (Soil_Moisture <= 62.50) {
                                if (Air_Humidity <= 69.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Temperature <= 6.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        } else {
                            if (Temperature <= 11.50) {
                                if (Temperature <= 9.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Temperature <= 14.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    } else {
                        if (Temperature <= 6.50) {
                            if (Soil_Moisture <= 81.50) {
                                if (Soil_Moisture <= 71.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Air_Humidity <= 69.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        } else {
                            if (Air_Humidity <= 64.50) {
                                if (Temperature <= 18.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Soil_Moisture <= 89.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (Temperature <= 28.50) {
                if (Air_Humidity <= 31.50) {
                    if (Air_Humidity <= 25.50) {
                        if (Temperature <= 24.50) {
                            if (Air_Humidity <= 23.50) {
                                if (Soil_Moisture <= 74.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Soil_Moisture <= 62.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        } else {
                            if (Soil_Moisture <= 87.50) {
                                if (Soil_Moisture <= 60.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Temperature <= 27.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    } else {
                        if (Temperature <= 26.50) {
                            if (Soil_Moisture <= 68.50) {
                                if (Air_Humidity <= 30.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                return 0;
                            }
                        } else {
                            if (Air_Humidity <= 27.50) {
                                if (Soil_Moisture <= 88.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Soil_Moisture <= 67.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    }
                } else {
                    if (Air_Humidity <= 55.50) {
                        if (Soil_Moisture <= 68.50) {
                            if (Air_Humidity <= 42.50) {
                                if (Soil_Moisture <= 66.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Air_Humidity <= 48.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Air_Humidity <= 33.50) {
                                if (Soil_Moisture <= 73.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Air_Humidity <= 35.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    } else {
                        if (Air_Humidity <= 63.50) {
                            if (Air_Humidity <= 59.50) {
                                if (Temperature <= 24.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Soil_Moisture <= 63.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        } else {
                            if (Soil_Moisture <= 89.50) {
                                if (Air_Humidity <= 66.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Temperature <= 26.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    }
                }
            } else {
                if (Soil_Moisture <= 69.50) {
                    if (Soil_Moisture <= 63.50) {
                        if (Air_Humidity <= 22.50) {
                            if (Temperature <= 39.50) {
                                if (Soil_Moisture <= 62.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Soil_Moisture <= 60.50) {
                                    return 1;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Air_Humidity <= 62.50) {
                                if (Air_Humidity <= 30.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Soil_Moisture <= 60.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    } else {
                        if (Temperature <= 35.50) {
                            if (Temperature <= 33.50) {
                                if (Air_Humidity <= 34.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Air_Humidity <= 21.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        } else {
                            if (Air_Humidity <= 69.50) {
                                if (Air_Humidity <= 20.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Soil_Moisture <= 64.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    }
                } else {
                    if (Air_Humidity <= 63.50) {
                        if (Soil_Moisture <= 72.50) {
                            if (Temperature <= 44.50) {
                                if (Temperature <= 29.50) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Air_Humidity <= 21.00) {
                                    return 1;
                                } else {
                                    return 0;
                                }
                            }
                        } else {
                            if (Temperature <= 30.50) {
                                if (Air_Humidity <= 61.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Air_Humidity <= 62.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            }
                        }
                    } else {
                        if (Soil_Moisture <= 78.50) {
                            if (Temperature <= 42.50) {
                                if (Temperature <= 29.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            } else {
                                if (Soil_Moisture <= 77.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            }
                        } else {
                            if (Soil_Moisture <= 83.50) {
                                if (Temperature <= 31.50) {
                                    return 0;
                                } else {
                                    return 0;
                                }
                            } else {
                                if (Temperature <= 43.50) {
                                    return 0;
                                } else {
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
#endif
